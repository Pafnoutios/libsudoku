#include "Sudoku/Grid.hpp"
#include "Sudoku/Solver.hpp"

#include <iostream>
#include <vector>


namespace Sudoku
{
  class Values
  {
  public:
    Values(const Grid& grid) : _grid(grid) {}

    friend std::ostream& operator<<(std::ostream& stream, const Values& values)
    {
      for (auto v : values._grid.values())
      {
        stream << v << ", ";
      }
      return stream;
    }

  private:
    const Grid& _grid;
  };


  bool solved(Sudoku::Grid const& grid)
  {
    auto values = grid.values();
    return std::none_of(values.cbegin(), values.cend(), [](int v) { return v == -1; });
  }
}


void runSolutions(int rank, const std::vector<int>& values)
{
  Sudoku::Grid p1(rank, values.cbegin(), values.cend());
  std::cout << "      Initial: " << Sudoku::Values(p1) << "\n";

  bool eitherSingle = false;

  Sudoku::Solver s1(p1);
  while (s1.nakedSingle())
  {
    std::cout << " Naked Single: "<< Sudoku::Values(p1) << "\n";
  }

  eitherSingle = solved(p1);

  std::cout << "\n";

  Sudoku::Grid p2(rank, values.cbegin(), values.cend());
  std::cout << "      Initial: " << Sudoku::Values(p2) << "\n";

  Sudoku::Solver s2(p2);
  while (s2.hiddenSingle())
  {
    std::cout << "Hidden Single: " << Sudoku::Values(p2) << "\n";
  }

  eitherSingle = eitherSingle || solved(p2);

  std::cout << "\n";

  if (!eitherSingle)
  {
    Sudoku::Grid p3(rank, values.cbegin(), values.cend());
    std::cout << "      Initial: " << Sudoku::Values(p3) << "\n";

    Sudoku::Solver s3(p3);
    bool done = false;
    while (!done)
    {
      eitherSingle = true;
      while (eitherSingle)
      {
        eitherSingle = false;
        while (s3.nakedSingle())
        {
          eitherSingle = true;
          std::cout << " Naked Single: " << Sudoku::Values(p3) << "\n";
        }
        while (s3.hiddenSingle())
        {
          eitherSingle = true;
          std::cout << "Hidden Single: " << Sudoku::Values(p3) << "\n";
        }
      }

      bool markedATuple = false;
      for (int size = 2; size <= rank && !markedATuple; ++size)
      {
        if ((markedATuple = s3.nakedTuple(size)))
        {
          std::cout << "  Naked " << size << "-ple: " << Sudoku::Values(p3) << "\n";
        }
        done = (size == rank);
      }
    }

    std::cout << "\n";
  }
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

  runSolutions(2, a);


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

  runSolutions(3, b);


  // +---+---+---+
  // |1 8|9 6| 5 |
  // |  2| 73| 1 |
  // |9  |8  |76 |
  // +---+---+---+
  // |4 7|   |   |
  // |  5|73 |   |
  // |   |6 5| 9 |
  // +---+---+---+
  // |   |5 8| 31|
  // |   | 4 |  8|
  // |  6| 9 |2  |
  // +---+---+---+
  const std::vector<int> c = {
     0, -1,  7,   8, -1,  5,  -1,  4, -1,
    -1, -1,  1,  -1,  6,  2,  -1,  0, -1,
     8, -1, -1,   7, -1, -1,   6,  5, -1,

     3, -1,  6,  -1, -1, -1,  -1, -1, -1,
    -1, -1,  4,   6,  2, -1,  -1, -1, -1,
    -1, -1, -1,   5, -1,  4,  -1,  8, -1,

    -1, -1, -1,   4, -1,  7,  -1,  2,  0,
    -1, -1, -1,  -1,  3, -1,  -1, -1,  7,
    -1, -1,  5,  -1,  8, -1,   1, -1, -1
  };

  runSolutions(3, c);


  // +---+---+---+
  // |7  |  6|  4|
  // |  9|   |   |
  // | 2 |  3|81 |
  // +---+---+---+
  // |312|   | 97|
  // |   |  4| 26|
  // |   |2  |   |
  // +---+---+---+
  // | 4 |5  |   |
  // | 9 |3  | 78|
  // |   |1  |2  |
  // +---+---+---+
  const std::vector<int> d = {
     6, -1, -1,  -1, -1,  5,  -1, -1,  3,
    -1, -1,  8,  -1, -1, -1,  -1, -1, -1,
    -1,  1, -1,  -1, -1,  2,   7,  0, -1,

     2,  0,  1,  -1, -1, -1,  -1,  8,  6,
    -1, -1, -1,  -1, -1,  3,  -1,  1,  5,
    -1, -1, -1,   1, -1, -1,  -1, -1, -1,

    -1,  3, -1,   4, -1, -1,  -1, -1, -1,
    -1,  8, -1,   2, -1, -1,  -1,  6,  7,
    -1, -1, -1,   0, -1, -1,   1, -1, -1
  };

  runSolutions(3, d);


  // +---+---+---+
  // |  5|  4|1  |
  // | 8 | 9 |   |
  // |   |   |832|
  // +---+---+---+
  // |5  |6 2|  4|
  // | 9 |  1|2 7|
  // |  2|5  |   |
  // +---+---+---+
  // |  6|   |  8|
  // |  8|76 | 2 |
  // | 4 |   |   |
  // +---+---+---+
  const std::vector<int> e = {
    -1, -1,  4,  -1, -1,  3,   0, -1, -1,
    -1,  7, -1,  -1,  8, -1,  -1, -1, -1,
    -1, -1, -1,  -1, -1, -1,   7,  2,  1,

     4, -1, -1,   5, -1,  1,  -1, -1,  3,
    -1,  8, -1,  -1, -1,  0,   1, -1,  6,
    -1, -1,  1,   4, -1, -1,  -1, -1, -1,

    -1, -1,  5,  -1, -1, -1,  -1, -1,  7,
    -1, -1,  7,   6,  5, -1,  -1,  1, -1,
    -1,  3, -1,  -1, -1, -1,  -1, -1, -1
  };

  runSolutions(3, e);


  // +---+---+---+
  // |   |   |   |
  // |   |  1| 98|
  // |  5|7  | 3 |
  // +---+---+---+
  // |  6| 5 |8 1|
  // |   | 6 |   |
  // | 7 |9  |   |
  // +---+---+---+
  // | 68|   |4 7|
  // |34 |   |   |
  // | 9 |5 2|6  |
  // +---+---+---+
  const std::vector<int> f = {
    -1, -1, -1,  -1, -1, -1,  -1, -1, -1,
    -1, -1, -1,  -1, -1,  0,  -1,  8,  7,
    -1, -1,  4,   6, -1, -1,  -1,  2, -1,

    -1, -1,  5,  -1,  4, -1,   7, -1,  0,
    -1, -1, -1,  -1,  5, -1,  -1, -1, -1,
    -1,  6, -1,   8, -1, -1,  -1, -1, -1,

    -1,  5,  7,  -1, -1, -1,   3, -1,  6,
     2,  3, -1,  -1, -1, -1,  -1, -1, -1,
    -1,  8, -1,   4, -1,  1,   5, -1, -1
  };

  runSolutions(3, f);
}
