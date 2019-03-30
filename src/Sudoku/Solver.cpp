#include "Solver.hpp"

#include "Cell.hpp"
#include "Grid.hpp"

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
    return true;
  }
  else
  {
    return false;
  }
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