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
  const std::vector<int> a = {
	  -1, -1,   2, -1,
	  -1, -1,   1,  3,

	   0,  2,  -1, -1,
	  -1,  1,  -1, -1
  };

  Sudoku::Grid p1(2, a.cbegin(), a.cend());
  printValues(p1);

  Sudoku::Solver s1(p1);
  for (int i = 0; i < 10; ++i)
  {
    s1.nakedSingle();
    printValues(p1);
  }

  std::cout << "\n";

  Sudoku::Grid p2(2, a.cbegin(), a.cend());
  printValues(p2);

  Sudoku::Solver s2(p2);
  for (int i = 0; i < 10; ++i)
  {
	  s2.hiddenSingle();
	  printValues(p2);
  }

  std::cout << "\n";

  // +---+---+---+
  // | 51|3 9|  6|
  // | 2 |871|345|
  // |   |2  |   |
  // +---+---+---+
  // |219|764| 3 |
  // |   |13 |   |
  // |73 |  8| 62|
  // +---+---+---+
  // |5  |42 |  3|
  // |   |915|  7|
  // |19 |   |2  |
  // +---+---+---+
  const std::vector<int> b = {
	  -1,  4,  0,   2, -1,  8,  -1, -1,  5,
	  -1,  1, -1,   7,  6,  0,   2,  3,  4,
	  -1, -1, -1,   1, -1, -1,  -1, -1, -1,

	   1,  0,  8,   6,  5,  3,  -1,  2, -1,
	  -1, -1, -1,   0,  2, -1,  -1, -1, -1,
	   6,  2, -1,  -1, -1,  7,  -1,  5,  1,

	   4, -1, -1,   3,  1, -1,  -1, -1,  2,
	  -1, -1, -1,   8,  0,  4,  -1, -1,  6,
	   0,  8, -1,  -1, -1, -1,   1, -1, -1
  };

  Sudoku::Grid p3(3, b.cbegin(), b.cend());
  printValues(p3);

  Sudoku::Solver s3(p3);
  for (int i = 0; i < 50; ++i)
  {
	  s3.nakedSingle();
	  printValues(p3);
  }

  std::cout << "\n";

  Sudoku::Grid p4(3, b.cbegin(), b.cend());
  printValues(p4);

  Sudoku::Solver s4(p4);
  for (int i = 0; i < 10; ++i)
  {
	  s4.hiddenSingle();
	  printValues(p4);
  }

  std::cout << "\n";
}
