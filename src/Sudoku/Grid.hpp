#pragma once


#include "Cell.hpp"
#include "Size.hpp"
#include "Slice.hpp"

#include <vector>


namespace Sudoku
{
  class Grid
  {
  public:
    Grid(int rank);

  private:
    Size _size;
    std::vector<Cell> _cells{_size[iGrid], Cell(_size)};
    std::vector<Slice> _rows{_size[iBlock], Slice(_size)};
    std::vector<Slice> _columns{_size[iBlock], Slice(_size)};
    std::vector<Slice> _blocks{_size[iBlock], Slice(_size)};
  };
}
