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

    bool isFilled() const noexcept { return _possibilities.empty(); }

    std::vector<int> possibilities() const { return _possibilities; }
    std::vector<Cell*> wherePossible(int i) const;

    std::vector<Cell*> members() { return _members; }

  private:

    std::vector<int> _possibilities;
    std::vector<Cell*> _members;
  };
}
