#pragma once


#include <array>


namespace Sudoku
{
  enum Sizes
  {
    iRank,
    iBlock,
    iGrid,
    numSizes
  };

  /// { block side length, block cell count = puzzle side length, puzzle cell count }
  /// For a standard puzzle, these are {3, 9, 81}.
  using Size = std::array<int, numSizes>;

  inline constexpr Size make_size(int rank)
  {
    int block = rank * rank;
    int puzzle = block * block;
    return { rank, block, puzzle };
  }
}
