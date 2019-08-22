#include "Slice.hpp"

#include "Cell.hpp"
#include <numeric>


Sudoku::Slice::Slice(const Size & size)
  : _possibilities{size[iBlock]}
  , _members{size[iBlock], nullptr}
{
  std::iota(_possibilities.begin(), _possibilities.end(), 0);
}

void Sudoku::Slice::assignMember(int index, Cell & cell)
{
  _members[index] = &cell;
}


void Sudoku::Slice::eliminatePossibility(int possibility, Cell * source)
{
  _possibilities.erase(std::remove(_possibilities.begin(), _possibilities.end(), possibility), _possibilities.end());

  for (auto cell : _members)
  {
    if (cell != source)
    {
      cell->eliminatePossibility(possibility);
    }
  }
}


std::vector<Sudoku::Cell*> Sudoku::Slice::wherePossible(int i) const
{
	std::vector<Cell*> possibilities;
	std::copy_if(_members.begin(), _members.end(), std::back_inserter(possibilities),
		[i](Cell const* cell) { return cell->isPossible(i); });
	return possibilities;
}
