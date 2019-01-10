#pragma once


#include "Grid.hpp"


namespace Sudoku
{
  class Puzzle
  {
  public:

    template<class FwdIt>
    Puzzle(int rank, FwdIt first, FwdIt last);

    std::vector<int> values() const { return _grid.values(); }

  private:

    Grid _grid;
  };
}


template<class FwdIt>
Sudoku::Puzzle::Puzzle(int rank, FwdIt first, FwdIt last)
  : _grid(rank, first, last)
{ }
