#pragma once


#include <vector>


namespace Sudoku
{
  class Cell;
  class Grid;
  class Slice;


  class Solver
  {
  public:
    Solver(Grid& grid);

    /**
    \brief  Marks one cell with a naked single.
    \return If it found a naked single to mark.
    */
    bool nakedSingle();

  private:

    void removeMarkedCells();
    void removeFilledSlices();

    Grid& _grid;

    std::vector<Cell*> _unmarkedCells;
    std::vector<Slice*> _unfilledSlices;
  };
}
