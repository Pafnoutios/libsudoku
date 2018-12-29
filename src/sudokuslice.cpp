/**
 * @file			sudokuslice.cpp
 * @author		John Szwast
 * @date			2013
 * @copyright	None permitted.
 */


#include <assert.h>
#include <set>
#include <stddef.h>
#include <algorithm>
#include "sudokuslice.h"
#include "sudokucell.h"


SudokuSlice::SudokuSlice(int const * size, SudokuSlice::Type slicetype)
:	Size(size)
,	SliceType(slicetype)
,	Members()
,	MemberCellMarks()
{
}


SudokuSlice::~SudokuSlice()
{
	delete[] MemberCellMarks;
}


void SudokuSlice::AssignMember(SudokuCell* newmember)
{
	Members.insert(newmember);
	return;
}


SudokuSlice::Type SudokuSlice::getSliceType() const
{
	return SliceType;
}


/**
 * Marks the value marked in the slice.
 * Calls EliminatePossibility on all other member cells
 * of the slice.
 */
void SudokuSlice::MarkUsedValue(int ValueToMark, SudokuCell* CellWhereMarked)
{
	MemberCellMarks.insert(ValueToMark);
	for(SudokeCell* member : Members)
	{
		if (member != CellWhereMarked)
			member->EliminatePossibility(ValueToMark);
	}
	return;
}


void SudokuSlice::DropMembers()
{
	Members.clear();
	return;
}


int SudokuSlice::getNumberOpenCells() const
{
	return Members.size() - MemberCellMarks.size();
}


bool SudokuSlice::isMarked(int value) const
{
	return MemberCellMarks.find(value) != MemberCellMarks.end();
}


std::set<SudokuCell*> SudokuSlice::getCellsWherePossible(int value) const
{
	assert(value < Size[1]);
	std::set<SudokuCell*> Possibles;
	std::copy_if(Members.begin(), Members.end(), std::back_inserter(Possibles),
							 [value](SudokuCell const * cell) { return cell->IsPossible(value); });
	return Possibles;
}


bool SudokuSlice::MarkNakedTuple(int n)
{
	bool ret_FoundOne = false;
	int *Tuple = new int[n];
	Tuple[0] = -1;
	int IncrementerMark = 0;
	std::set<int> Possibilities;
	
	while((!ret_FoundOne) && (Tuple[0] < Size[1]))
	{
		++Tuple[IncrementerMark];
		if (Tuple[IncrementerMark] >= Size[1])
		{
			--IncrementerMark;
		}
		else if ((!Members[Tuple[IncrementerMark]]->IsMarked())
			&& (Members[Tuple[IncrementerMark]]->getNumberPossibilities() <= n))
		{
			// This cell has that many possible
			if (IncrementerMark == n-1)
			{
				// We've found n cells with (up to) n possibilities each.
				Possibilities.clear();
				for (int CellCounterIndex = 0; CellCounterIndex < n; CellCounterIndex++)
				{
					for (int PossibilityIndex = 0; 
						PossibilityIndex < Members[Tuple[CellCounterIndex]]->getNumberPossibilities(); 
						PossibilityIndex++)
					{
						Possibilities.insert(Members[Tuple[CellCounterIndex]]->getNthPossibility(PossibilityIndex+1));
					}
				}
				
				if (Possibilities.size() <= n)
				{
					// Less than n is a big oops.
					assert(Possibilities.size() == n);
					// We've found one that matters if any other cells in this slice still think these are possible for them.
					for (std::set<int>::iterator NakedIterator = Possibilities.begin();
							 NakedIterator != Possibilities.end(); NakedIterator++)
					{
						for (int cell_index = 0, tuple_index = 0; cell_index < Size[1]; ++cell_index)
							if (cell_index == Tuple[tuple_index])
								++tuple_index;	// Skip the ones where we've found them, and be ready to skip the next one.
							else
								ret_FoundOne = ret_FoundOne || Members[cell_index]->IsPossible(*NakedIterator);
					}
				}
			}
			else	// IncrementerMark not done yet.
			{
				Tuple[IncrementerMark+1] = Tuple[IncrementerMark];
				++IncrementerMark;
			}
		}
		// else keep incrementing the same.
	}
	
	if (ret_FoundOne)
	{
		// Remove each possibility in the naked n-tuple from each other Cell.
		for (std::set<int>::iterator NakedIterator = Possibilities.begin();
			 NakedIterator != Possibilities.end(); NakedIterator++)
		{
			IncrementerMark = 0;	// Will now mark the naked cells to skip over.
			for (int CellIndex = 0; CellIndex < Size[1]; CellIndex++)
			{
				if (CellIndex == Tuple[IncrementerMark])	// Don't eliminate from the naked tuple.
				{
					IncrementerMark++;	// Be ready to skip the next naked cell.
				}
				else
				{
					Members[CellIndex]->EliminatePossibility(*NakedIterator);
				}
			}
		}
	}
	
	delete[] Tuple;
	
	return ret_FoundOne;
}

