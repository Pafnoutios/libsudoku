/**
 * @file       sudokucell.h
 * @author     John Szwast
 * @date       2013
 * @copyright  None permitted.
 */


#pragma once


#include <set>
#include "sudokuslice.h"


class SudokuCell
{
	public:

		SudokuCell(const std::array<int, 3>& size);
		~SudokuCell();

		int getValue() const;
		SudokuSlice* getMembership(SudokuSlice::Type slicetype) const;
		void AssignMembership(SudokuSlice* slice, SudokuSlice::Type slicetype);
		bool SetPossibility(int possibility);
		bool EliminatePossibility(int possibility);
		int getNumberPossibilities() const;
		std::set<int> getPossibilities() const;
		bool IsPossible(int possibility) const;
		bool IsMarked() const;
		bool setValue(int value);
		void Initialize();

	private:

		const std::array<int, 3>& Size;
		std::set<int> Possibilities;
		std::map<SudokuSlice::Type, SudokuSlice *> Memberships;
		bool Marked;
		int Value;
		
};

