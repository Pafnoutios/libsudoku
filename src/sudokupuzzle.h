/**
 * @file			sudokupuzzle.h
 * @author		John Szwast
 * @date			2013
 * @copyright	None permitted.
 */


#pragma once


class SudokuCell;
class SudokuSlice;


class SudokuPuzzle
{
	
	public:
	
		enum Difficulty
		{
			UNDETERMINED = -1,
			NAKED_OR_HIDDEN_SINGLES,
			NAKED_AND_HIDDEN_SINGLES
		};
		
		static char const DefaultAlphabets[7][36];
		
		SudokuPuzzle(int size);
		SudokuPuzzle(int size, int *import);
		SudokuPuzzle(SudokuPuzzle const &source);
		SudokuPuzzle(SudokuPuzzle const *source);
		~SudokuPuzzle();

		bool operator==(const SudokuPuzzle& B);
		void Import(int* inputarray);
		int* Export() const;
		int getsize() const;
		int Solve();

	private:
	
		void AllocatePuzzlePieces(int size);
		void Initialize();
		int SolveByNakedSingles();
		int SolveByHiddenSingles();
		int NumberOpenCells() const;
		int SolveBySingles();
		bool MarkANakedTuple(int n);
		int SolveWithNakedTuples(int n);

		int* Size;
		SudokuCell** PuzzleCells;
		SudokuSlice** PuzzleRows;
		SudokuSlice** PuzzleCols;
		SudokuSlice*** PuzzleBlocks;
		Difficulty Diff;
		
};
