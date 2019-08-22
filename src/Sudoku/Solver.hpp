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
    \return Whether it found a naked single to mark, i.e. keep looking for more.
    */
    bool nakedSingle();

	/**
	 *	\brief	Marks one cell with a hidden single.
	 *	\return	Whether it found a hidden single to mark, i.e. keep looking for more.
	 */
	bool hiddenSingle();

  private:

    void removeMarkedCells();
    void removeFilledSlices();

    Grid& _grid;

    std::vector<Cell*> _unmarkedCells;
    std::vector<Slice*> _unfilledSlices;
  };
}
