#include "Sudoku/Grid.hpp"
#include "Sudoku/Solver.hpp"

#include <iostream>
#include <vector>


void printValues(Sudoku::Grid const& grid)
{
  auto values = grid.values();
  for (auto v : values)
  {
    std::cout << v << ", ";
  }
  std::cout << "\n";
}


int main()
{
  // +--+--+
  // |  |3 |
  // |  |24|
  // +--+--+
  // |13|  |
  // | 2|  |
  // +--+--+
  std::vector<int> a = {-1, -1, 2, -1,  -1, -1, 1, 3,  0, 2, -1, -1,  -1, 1, -1, -1};

  Sudoku::Grid p(2, a.cbegin(), a.cend());
  printValues(p);

  Sudoku::Solver s(p);
  for (int i = 0; i < 10; ++i)
  {
    s.nakedSingle();
    printValues(p);
  }
}
