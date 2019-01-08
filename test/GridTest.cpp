#include "Sudoku/Grid.hpp"

#include <iostream>


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
  auto b = p.values();

  for (auto v : b)
    std::cout << v << ", ";
}
