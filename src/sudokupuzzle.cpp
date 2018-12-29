/**
 * @file			sudokupuzzle.cpp
 * @author		John Szwast
 * @date			2012
 * @copyright	None permitted.
 */


#include "sudokupuzzle.h"
#include "sudokucell.h"
#include "sudokuslice.h"
#include <stddef.h>

/**
 * @brief Standard Constructor
 * @details	Allocates all Cells and Slices.  Assigns memberships of cells and slices.  Leaves puzzle blank with all values possible in each Cell.
 * @param[in]	size	Size of one dimension of puzzle.
 */
SudokuPuzzle::SudokuPuzzle(int size)
{
	AllocatePuzzlePieces(size);
}

/**
 * @brief Constructor with initializer
 * @details	Generates a puzzle with the given symbols predefined.
 * @param[in]	size		Size of one dimension of the puzzle.
 * @param[in]	import	Pointer to int[size^4] of cell entries.
 */
SudokuPuzzle::SudokuPuzzle(int size, int *import)
{
	AllocatePuzzlePieces(size);
	Import(import);
}

/**
 * @brief Copy Constructor
 * @details	Allocates all Cells and Slices.  Assigns memberships of cells and slices.  Copies marked values from source cells.
 * @param[in]	source	Source puzzle to copy.
 */
SudokuPuzzle::SudokuPuzzle(const SudokuPuzzle &source)
{
	AllocatePuzzlePieces(source.getsize());
	
	for(int i = 0; i < Size[2]; i++)
		PuzzleCells[i]->setValue(source.PuzzleCells[i]->getValue());
}

/**
 * @brief "Copy" Constructor
 * @details	Allocates all Cells and Slices.  Assigns memberships of cells and slices.  Copies marked values from source cells.
 * @param[in]	source	Source puzzle to copy.
 */
SudokuPuzzle::SudokuPuzzle(SudokuPuzzle const *source)
{
	AllocatePuzzlePieces(source->getsize());
	
	for(int i = 0; i < Size[2]; i++)
		PuzzleCells[i]->setValue(source->PuzzleCells[i]->getValue());
}

/**
 * @brief Allocates all memory for Puzzle Cells and Slices.
 * @param[in]	size	Size of one dimension of puzzle.
 */
void SudokuPuzzle::AllocatePuzzlePieces(int size)
{
	Diff = UNDETERMINED;
	
	Size = new int[3];
	Size[0] = size;
	Size[1] = size * size;
	Size[2] = Size[1] * Size[1];

	// Generate arrays of pointers.
	PuzzleCells = new SudokuCell*[Size[2]];
	for(int i = 0; i < Size[2]; i++)
		PuzzleCells[i] = new SudokuCell(Size);
	
	PuzzleRows = new SudokuSlice*[Size[1]];
	PuzzleCols = new SudokuSlice*[Size[1]];
	for(int i = 0; i < Size[1]; i++)
	{
		PuzzleRows[i] = new SudokuSlice(Size, SudokuSlice::ROW);
		PuzzleCols[i] = new SudokuSlice(Size, SudokuSlice::COLUMN);
	}
	
	PuzzleBlocks = new SudokuSlice**[Size[0]];
	for(int i = 0; i < Size[0]; i++)
	{
		PuzzleBlocks[i] = new SudokuSlice*[Size[0]];
		for(int j = 0; j < Size[0]; j++)
			PuzzleBlocks[i][j] = new SudokuSlice(Size, SudokuSlice::BLOCK);
	}
	
	// Assign memberships.
	for(int i = 0; i < Size[0]; i++)	// (i,j) addresses blocks
		for(int j = 0; j < Size[0]; j++)
			for(int k = 0; k < Size[0]; k++)	// (k,l) addresses cells in a block
				for(int l = 0; l < Size[0]; l++)
				{
					//	+---+---+---+
					//	|   |   |   |
					//	|   |   |   |
					//	|   |   |   |
					//	+---+---+---+
					//	|   |   | * |	This marked cell is in block (1,2), subcell (0,1).
					//	|   |   |   |
					//	|   |   |   |
					//	+---+---+---+
					//	|   |   |   |
					//	|   |   |   |
					//	|   |   |   |
					//	+---+---+---+
					
					int cell_row = Size[0]*i + k;
					int cell_col = Size[0]*j + l;
					
					PuzzleCells[Size[1]*cell_row + cell_col]->AssignMembership(PuzzleRows[cell_row], SudokuSlice::ROW);
					PuzzleCells[Size[1]*cell_row + cell_col]->AssignMembership(PuzzleCols[cell_col], SudokuSlice::COLUMN);
					PuzzleCells[Size[1]*cell_row + cell_col]->AssignMembership(PuzzleBlocks[i][j], SudokuSlice::BLOCK);
					
					PuzzleRows[cell_row]->AssignMember(PuzzleCells[Size[1]*cell_row + cell_col]);
					PuzzleCols[cell_col]->AssignMember(PuzzleCells[Size[1]*cell_row + cell_col]);
					PuzzleBlocks[i][j]->AssignMember(PuzzleCells[Size[1]*cell_row + cell_col]);
				}
}



SudokuPuzzle::~SudokuPuzzle()
{
	int i;
	
	if(PuzzleCols != NULL)
		for(i = 0; i < Size[1]; i++)
			if(PuzzleCols[i] != NULL)
			{
				PuzzleCols[i]->DropMembers();
				delete PuzzleCols[i];
			}
	delete[] PuzzleCols;
	PuzzleCols = NULL;
	
	if(PuzzleRows != NULL)
		for(i = 0; i < Size[1]; i++)
			if(PuzzleRows[i] != NULL)
			{
				PuzzleRows[i]->DropMembers();
				delete PuzzleRows[i];
			}
	delete[] PuzzleRows;
	PuzzleRows = NULL;
	
	if(PuzzleBlocks != NULL)
		for(i = 0; i < Size[0]; i++)
		{
			for(int j = 0; j < Size[0]; j++)
				if(PuzzleBlocks[i][j] != NULL)
				{
					PuzzleBlocks[i][j]->DropMembers();
					delete PuzzleBlocks[i][j];
				}
			delete[] PuzzleBlocks[i];
		}
	delete[] PuzzleBlocks;
	PuzzleBlocks = NULL;
	
	if(PuzzleCells != NULL)
		for(i = 0; i < Size[2]; i++)
			if(PuzzleCells[i] != NULL)
			{
				PuzzleCells[i]->ClearMemberships();
				delete PuzzleCells[i];
			}
	delete[] PuzzleCells;
	
	delete[] Size;
}

bool SudokuPuzzle::operator==(const SudokuPuzzle& B)
{
	bool ret_equal = true;
	int i;
	
	if(B.Size[0] != Size[0])
		ret_equal = false;
	else
		for(i = 0; i < Size[2]; i++)
			if(PuzzleCells[i]->getValue() != B.PuzzleCells[i]->getValue())
				ret_equal = false;
			
	return ret_equal;
}

/**
 * inputarray should be a pointer to a Size[2]-size array of puzzle cell values.
 */
void SudokuPuzzle::Import(int* inputarray)
{
	Initialize();
	
	for(int i = 0; i < Size[2]; i++)
		PuzzleCells[i]->setValue(inputarray[i]);
	
	delete [] inputarray;
}

int* SudokuPuzzle::Export() const
{
	int* ret_ValuesArray = new int[Size[2]];
	
	for(int i = 0; i < Size[2]; i++)
		ret_ValuesArray[i] = PuzzleCells[i]->getValue();
	
	return ret_ValuesArray;
}

int SudokuPuzzle::getsize() const
{
	return Size[0];
}

void SudokuPuzzle::Initialize()
{
	for(int i = 0; i < Size[2]; i++)
		PuzzleCells[i]->Initialize();
	
	for(int i = 0; i < Size[0]; i++)
		for(int j = 0; j < Size[0]; j++)
		{
			PuzzleRows[Size[0]*i+j]->Initialize();
			PuzzleCols[Size[0]*i+j]->Initialize();
			PuzzleBlocks[i][j]->Initialize();
		}
}

char const SudokuPuzzle::DefaultAlphabets[7][36] = {{0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,
														0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},	// size 0
														{0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,
														0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},	// size 1
														{'1','2','3','4',0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,
														0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},	// size 2
														{'1','2','3','4','5','6', '7','8','9',0,0,0, 0,0,0,0,0,0,
														0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},	// size 3
														{'1','2','3','4','5','6', '7','8','9','A','B','C', 'D','E','F',0,0,0,
														0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},	// size 4
														{'A','B','C','D','E','F', 'G','H','I','J','K','L', 
														'M','N','O','P','Q','R', 'S','T','U','V','W','X',
														'Y',0,0,0,0,0, 0,0,0,0,0,0},	// size 5
														{'0','1','2','3','4','5', '6','7','8','9','A','B',
														'C','D','E','F','G','H', 'I','J','K','L','M','N',
														'O','P','Q','R','S','T', 'U','V','W','X','Y','Z'}};	// size 6

int SudokuPuzzle::Solve()
{
	SudokuPuzzle* ByNakedSingle = new SudokuPuzzle(this);
	SudokuPuzzle* ByHiddenSingle = new SudokuPuzzle(this);
	int ret_difficulty = -1;
	
	// Try each single method first.
	int NakedOpenCells = ByNakedSingle->SolveByNakedSingles();
	int HiddenOpenCells = ByHiddenSingle->SolveByHiddenSingles();
	
	if ((NakedOpenCells == 0) && (HiddenOpenCells == 0))
	{
		SolveByHiddenSingles();
		ret_difficulty = 0;
	}
	else if (HiddenOpenCells == 0)
	{
		SolveByHiddenSingles();
		ret_difficulty = 1;
	}
	else if (NakedOpenCells == 0)
	{
		SolveByNakedSingles();
		ret_difficulty = 1;
	}
	else if(SolveBySingles() == 0)
	{
		// Try the single methods together.
		ret_difficulty = 1;
	}
	else if(SolveWithNakedTuples(2) == 0)
		ret_difficulty = 2;
	else if(SolveWithNakedTuples(3) == 0)
		ret_difficulty = 3;
	
	delete ByNakedSingle;
	delete ByHiddenSingle;
	
	return ret_difficulty;
}


/**
 * @brief	Attempts to solve the puzzle by only Naked Singles.
 * @returns	The number of cells still open; 0 means solved.
 */
int SudokuPuzzle::SolveByNakedSingles()
{
	SudokuCell** SemiSortedArray;
	bool done=false;
	
	SemiSortedArray = new SudokuCell*[Size[2]];
	
	int NumberUnsolved = 0;	// Will keep count of the number of unmarked cells
	for(int i = 0; i < Size[2]; i++)
		if(PuzzleCells[i]->getValue() == -1)
			SemiSortedArray[NumberUnsolved++] = PuzzleCells[i];
	
	if(NumberUnsolved == 0)
		done = true;
		
	while(!done)
	{
		// Semi sort array of pointers by number of possibilities;
		// In reverse order, Cells with less number of possibilities are at the end.
		// I have to keep re-semi-sorting the array, because every time a Cell gets marked,
		// it can affect the number of possibilities in many other cells.
		for(int gopher = 0; gopher < NumberUnsolved-1; gopher++)
			if(SemiSortedArray[gopher]->getNumberPossibilities() < SemiSortedArray[gopher+1]->getNumberPossibilities())
			{
				// If this Cell has fewer possibilities than the next, swap them.
				SudokuCell* temp;
				temp = SemiSortedArray[gopher];
				SemiSortedArray[gopher] = SemiSortedArray[gopher+1];
				SemiSortedArray[gopher+1] = temp;
			}
		//SemiSortedArray[NumberUnsolved-1] should be an unsolved cell with the least number of possibilities.

		if(SemiSortedArray[NumberUnsolved-1]->getNumberPossibilities() == 1)	// Naked singles are still possible
		{
			int i = SemiSortedArray[NumberUnsolved-1]->getFirstPossibility();
			SemiSortedArray[NumberUnsolved-1]->setValue(i);
			NumberUnsolved--;
			if(NumberUnsolved == 0)
				done = true;
		}
		else	// No more Naked singles are possible
			done = true; // but ret_val > 0;
	}
	
	delete[] SemiSortedArray;
	
	return NumberUnsolved;
}


/**
 * @brief Attempts to solve the puzzle by using only Hidden Singles.
 * @returns	The number of cells still open; 0 means solved.
 */
int SudokuPuzzle::SolveByHiddenSingles()
{
	int i, j, numpossible, k;
	bool tryagain = true;
	
	while(tryagain)
	{
		tryagain = false; // Set to true if anything is done to cycle through again.
		
		// Look for hidden singles by cell value
		for(int tryvalue = 0; tryvalue < Size[1]; tryvalue++)
		{
			// Look in blocks, rows, and columns
			for(i = 0; i < Size[0]; i++)
				for(j = 0; j < Size[0]; j++)
				{
					if(PuzzleBlocks[i][j]->NumberCellsWherePossible(tryvalue) == 1)
					{
						// Mark the value in the only cell in the block where the value is possible.
						(PuzzleBlocks[i][j]->getFirstWherePossible(tryvalue))->setValue(tryvalue);
						tryagain = true;
					}
					if(PuzzleRows[Size[0]*i+j]->NumberCellsWherePossible(tryvalue) == 1)
					{
						(PuzzleRows[Size[0]*i+j]->getFirstWherePossible(tryvalue))->setValue(tryvalue);
						tryagain = true;
					}
					if(PuzzleCols[Size[0]*i+j]->NumberCellsWherePossible(tryvalue) == 1)
					{
						(PuzzleCols[Size[0]*i+j]->getFirstWherePossible(tryvalue))->setValue(tryvalue);
						tryagain = true;
					}
				}
		}
	}
			
	return NumberOpenCells();
}


/**
 * @brief	Counts the number of open Cells in the puzzle.
 * @returns	The number of open cells.
 */
int SudokuPuzzle::NumberOpenCells() const
{
	int ret_cells = 0;
	for (int cell_index = 0; cell_index < Size[2]; cell_index++)
		if (!PuzzleCells[cell_index]->IsMarked())
			ret_cells++;
		
	return ret_cells;
}


int SudokuPuzzle::SolveBySingles()
{
	int old_open_cells = Size[2]+1;
	int new_open_cells = Size[2];
	// Try both until solved or no progress
	while(new_open_cells < old_open_cells)	// While making progress.
	{
		old_open_cells = new_open_cells;
		new_open_cells = SolveByHiddenSingles();
		new_open_cells = SolveByNakedSingles();
	}
	
	return new_open_cells;
}


/**
 * @brief Marks one Naked n-Tuple in the puzzle if it can be found.
 * @param[in]	n	Size of tuple.
 * @returns	Whether one was found (and marked).
 */
bool SudokuPuzzle::MarkANakedTuple(int n)
{
	bool ret_success = false;
	
	for (int RowIndex = 0; !ret_success && (RowIndex < Size[1]); RowIndex++)
		ret_success = PuzzleRows[RowIndex]->MarkNakedTuple(n);
	
	for (int ColIndex = 0; !ret_success && (ColIndex < Size[1]); ColIndex++)
		ret_success = PuzzleCols[ColIndex]->MarkNakedTuple(n);
	
	for (int BlockIndexi = 0; !ret_success && (BlockIndexi < Size[0]); BlockIndexi++)
		for (int BlockIndexj = 0; !ret_success && (BlockIndexj < Size[0]); BlockIndexj++)
			ret_success = PuzzleBlocks[BlockIndexi][BlockIndexj]->MarkNakedTuple(n);
	
	return ret_success;
}


int SudokuPuzzle::SolveWithNakedTuples(int n)
{
	if (n == 1)
		return SolveBySingles();
	else
	{
		int ret_OpenCells = SolveWithNakedTuples(n-1);
		
		while (MarkANakedTuple(n))
			ret_OpenCells = SolveWithNakedTuples(n-1);
	
		return ret_OpenCells;
	}
}

