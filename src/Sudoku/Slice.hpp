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

  private:

    std::vector<int> _possibilities;
    std::vector<Cell*> _members;
  };
}
