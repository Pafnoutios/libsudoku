/**
 * @file			sudokuslice.h
 * @author		John Szwast
 * @date			2013
 * @copyright	None permitted.
 */


#pragma once


#include <set>


class SudokuCell;


class SudokuSlice
{
	public:
		
		enum class Type
		{
			Row,
			Column,
			Block,
		};
		
		SudokuSlice(int const * size, Type slicetype);
		~SudokuSlice();
	
		void AssignMember(SudokuCell* newmember);
		Type getSliceType() const;
		void MarkUsedValue(int ValueToMark, SudokuCell* CellWhereMarked);
		void DropMembers();
		int getNumberOpenCells() const;
		bool isMarked(int value) const;
		std::set<SudokuCell*> getCellsWherePossible(int value) const;
		bool MarkNakedTuple(int n);

	private:

		const std::array<int, 3>& Size;
		Type SliceType;
		std::set<SudokuCell*> Members;
		std::set<int> MemberCellMarks;
};
