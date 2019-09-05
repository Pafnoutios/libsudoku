#include "Solver.hpp"

#include "Cell.hpp"
#include "Grid.hpp"

#include <combination_iterator.hpp>

#include <algorithm>
#include <memory>


Sudoku::Solver::Solver(Grid& grid)
  : _grid(grid)
  , _unmarkedCells(_grid._size[iGrid])
  , _unfilledSlices(3 * _grid._size[iBlock])
{
  auto address = [](auto& x) { return &x; };

  std::transform(_grid._cells.begin(), _grid._cells.end(), _unmarkedCells.begin(), address);
  removeMarkedCells();

  auto next = std::transform(_grid._rows.begin(), _grid._rows.end(), _unfilledSlices.begin(), address);
  next = std::transform(_grid._columns.begin(), _grid._columns.end(), next, address);
  std::transform(_grid._blocks.begin(), _grid._blocks.end(), next, address);
  removeFilledSlices();
}


bool Sudoku::Solver::nakedSingle()
{
  if (_unmarkedCells.empty()) return false;

  std::partial_sort(_unmarkedCells.rbegin(), _unmarkedCells.rbegin() + 1, _unmarkedCells.rend(),
    [](Cell* x, Cell* y) { return x->numPossibilities() < y->numPossibilities(); });

  auto& cell = _unmarkedCells.back();
  if (cell->numPossibilities() == 1)
  {
    cell->markValue(cell->possibilities()[0]);
    removeMarkedCells();
    removeFilledSlices();
    return true;
  }
  else
  {
    return false;
  }
}


bool Sudoku::Solver::hiddenSingle()
{
  for (auto slice : _unfilledSlices)
  {
    for (auto i : slice->possibilities())
    {
      auto cells = slice->wherePossible(i);
      if (cells.size() == 1)
      {
        cells[0]->markValue(i);
        removeMarkedCells();
        removeFilledSlices();
        return true;
      }
    }
  }
  return false;
}


bool Sudoku::Solver::nakedTuple(int n)
{
  for (auto& slice : _unfilledSlices)
  {
    if (slice->possibilities().size() >= n)
    {
      if (nakedTuple(*slice, n)) return true;
    }
  }

  return false;
}


void Sudoku::Solver::removeMarkedCells()
{
  _unmarkedCells.erase(std::remove_if(_unmarkedCells.begin(), _unmarkedCells.end(),
    [](Cell const* cell) { return cell->isMarked(); }),
    _unmarkedCells.cend());
}


void Sudoku::Solver::removeFilledSlices()
{
  _unfilledSlices.erase(std::remove_if(_unfilledSlices.begin(), _unfilledSlices.end(),
    [](Slice const* slice) { return slice->isFilled(); }),
    _unfilledSlices.cend());
}


bool Sudoku::Solver::nakedTuple(Slice& slice, int n)
{
  auto source = slice.members();
  std::set<Cell*> cells{ source.cbegin(), source.cend() };

  for (auto const& tuple : make_combinations(cells.cbegin(), cells.cend(), n))
  {
    if (std::all_of(tuple.cbegin(), tuple.cend(), [](Cell* cell) { return !cell->isMarked(); }))
    {
      std::set<int> possibilities;
      for (auto cell : tuple)
      {
        auto x = cell->possibilities();
        possibilities.insert(x.begin(), x.end());
      }

      if (possibilities.size() == n // and any other cell in the slice also has some of these possibilities.
        && std::any_of(source.cbegin(), source.cend(),
          [&tuple, &possibilities](Cell* cell)
          {
            auto cellPoss = cell->possibilities();
            std::vector<int> overlap;
            std::set_intersection(possibilities.cbegin(), possibilities.cend(), cellPoss.cbegin(), cellPoss.cend(), std::back_inserter(overlap));
            return tuple.find(cell) == tuple.cend() && !overlap.empty();
          })
        )
      {
        for (auto cell : cells)
        {
          for (auto possibility : possibilities)
          {
            if (tuple.find(cell) == tuple.end())
            {
              cell->eliminatePossibility(possibility);
            }
          }
        }

        return true;
      }
    }
  }

  return false;
}
