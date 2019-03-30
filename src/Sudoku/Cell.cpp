#include "Cell.hpp"

#include "Slice.hpp"
#include <algorithm>
#include <numeric>


Sudoku::Cell::Cell(const Size & size)
  : _possibilities(size[iBlock])
{
  std::iota(_possibilities.begin(), _possibilities.end(), 0);
}


void Sudoku::Cell::assignMembership(SliceType index, Slice & slice)
{
  _memberships[index] = &slice;
}


void Sudoku::Cell::eliminatePossibility(int possibility)
{
  _possibilities.erase(std::remove(_possibilities.begin(), _possibilities.end(), possibility), _possibilities.end());
}


void Sudoku::Cell::markValue(int value)
{
  if (value != -1)
  {
    _possibilities.clear();
    _marked = true;
    _value = value;

    for (auto slice : _memberships)
    {
      slice->eliminatePossibility(value, this);
    }
  }
}
