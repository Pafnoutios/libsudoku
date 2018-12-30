#pragma once


#include "Size.hpp"
#include "SliceType.hpp"
#include <array>
#include <vector>


namespace Sudoku
{
  class Slice;

  class Cell
  {
  public:

    static const int Unassigned = -1;

    Cell(const Size& size);

  private:

    std::vector<int> _possibilities;
    std::array<Slice*, numSliceTypes> _memberships;
    bool _marked = false;
    int _value = Unassigned;
  };
}
