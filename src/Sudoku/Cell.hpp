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

	bool isPossible(int i) const;
    void eliminatePossibility(int possibility);
    void markValue(int value);

    int value() const { return _value; }

    bool isMarked() const noexcept { return _marked; }
    std::size_t numPossibilities() const noexcept { return _possibilities.size(); }
    std::vector<int> const& possibilities() const noexcept { return _possibilities; }

  private:

    std::vector<int> _possibilities;
    std::array<Slice*, numSliceTypes> _memberships;
    bool _marked = false;
    int _value = Unassigned;
  };
}
