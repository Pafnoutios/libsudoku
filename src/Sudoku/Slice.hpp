#pragma once


#include "Size.hpp"

#include <vector>


namespace Sudoku
{
  class Cell;

  class Slice
  {
  public:
    Slice(const Size& size);

    void assignMember(int index, Cell& cell);

    void eliminatePossibility(int possibility, Cell* source);

  private:

    std::vector<int> _possibilities;
    std::vector<Cell*> _members;
  };
}
