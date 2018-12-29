/**
 * @file			sudokucell.cpp
 * @author		John Szwast
 * @date			2012
 * @copyright	None permitted.
 */


#include "sudokucell.h"
#include <assert.h>
#include <stddef.h>


/**
 * @brief Standard constructor.
 * @details	Initializes the size of the puzzle in the cell, the value of the cell to -1 (unknown), that the cell is not yet marked, and the array of possibilities to undetermined.
 */
SudokuCell::SudokuCell(const std::array<int, 3>& size)
:	Size(size)
{
	Initialize();
}


/**
 * @brief	Standard deconstructor.
 * @details	Clears the dynamic array of possibilities.
 */
SudokuCell::~SudokuCell()
{
}


int SudokuCell::getValue() const
{
	return Value;
}


/**
 * \returns A pointer to the row, column, or block 
 * of which the cell is a member.
 */
SudokuSlice* SudokuCell::getMembership(SudokuSlice::Type slicetype) const
{
	return Memberships[slicetype];
}


void SudokuCell::AssignMembership(SudokuSlice* slice, SudokuSlice::Type slicetype)
{
	Memberships[slicetype] = slice;
	return;
}


bool SudokuCell::SetPossibility(int possibility)
{
	assert(possibility < Size[1]);
	if (Marked && (Value != possibility))
		return false;

	Possibilities += possibility;
	
	return true;
}


bool SudokuCell::EliminatePossibility(int possibility)
{
	assert(possibility < Size[1]);
	if (Marked)
		return false;
	
	Possibilities -= possibility;
	
	return true;
}


int SudokuCell::getNumberPossibilities() const
{
	return Possibilities.size();
}


std::set<int> SudokuCell::getPossibilities() const
{
	return Possibilities;
}


bool SudokuCell::IsPossible(int possibility) const
{
	assert(possibility < Size[1]);
	return Possibilities.find(possibility) != Possibilities.end();
}


bool SudokuCell::IsMarked() const
{
	return Marked;
}


bool SudokuCell::setValue(int value)
{
	assert(value < Size[1]);
	bool ret_val=true;
	
	if(value == -1)	// The SudokuPuzzle copy constructor will blindly pass this value.
	{			// So do some other SudokuPuzzle functions.
		assert (Value == -1);
		Value = value;
	}
	else if(0 <= value && value < Size[1] && IsPossible(value))	//Verify valid input
	{
		Value = value;
		// Eliminate all other values as possibilities
		Possibilities = {value};
		Marked = true;
		/*
		* Notify Block, Row, and Col that this value is now used
		* in them, and by which cell.  Each Slice is responsible
		* for notifying its other member cells that this value is
		* no longer possible for them.
		*/
		for (auto i : SudokuSlice::Type)
		{
			assert(Memberships[i] != NULL);
			Memberships[i]->MarkUsedValue(value, this);
		}
	}
	else	//for invalid input
		ret_val=false;
	
	return ret_val;
}


void SudokuCell::Initialize()
{
	Marked = false;
	Value = -1;
	for(int i = 0; i < Size[1]; i++)
		Possibilities.insert(i);
	
	return;
}
