#include "Cell.hpp"

#include <numeric>


Sudoku::Cell::Cell(const Size & size)
  : _possibilities{size[iBlock]}
{
  std::iota(_possibilities.begin(), _possibilities.end(), 0);
}
