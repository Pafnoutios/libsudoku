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

    template<class FwdIt>
    Grid(int rank, FwdIt first, FwdIt last);

    std::vector<int> values() const;

  private:

    friend class Solver;

    void assignMemberships();

    Size _size;
    std::vector<Cell> _cells{ _size[iGrid], Cell(_size) };
    std::vector<Slice> _rows{ _size[iBlock], Slice(_size) };
    std::vector<Slice> _columns{ _size[iBlock], Slice(_size) };
    std::vector<Slice> _blocks{ _size[iBlock], Slice(_size) };
  };
}


template<class FwdIt>
Sudoku::Grid::Grid(int rank, FwdIt first, FwdIt last)
  : _size(make_size(rank))
{
  assignMemberships();
  for (auto cell = _cells.begin();
    cell != _cells.end() && first != last;
    ++cell, ++first)
  {
    cell->markValue(*first);
  }
}


