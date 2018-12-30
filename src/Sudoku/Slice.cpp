#include "Slice.hpp"

#include <numeric>


Sudoku::Slice::Slice(const Size & size)
  : _possibilities{size[iBlock]}
  , _members{size[iBlock], nullptr}
{
  std::iota(_possibilities.begin(), _possibilities.end(), 0);
}
