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

    void assignMembership(SliceType index, Slice& slice);

    void eliminatePossibility(int possibility);
    void markValue(int value);

    int value() const { return _value; }

  private:

    std::vector<int> _possibilities;
    std::array<Slice*, numSliceTypes> _memberships;
    bool _marked = false;
    int _value = Unassigned;
  };
}
