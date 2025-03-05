// Project Maze
// FileName : gameboard.cpp
// Author: Christian Siletti
// Purpose : This file contains the implementation for all of the methods
//			 defined in gameboard.h

#include "gameboard.h"	// The header file
#include <new>			// Contains the bad_alloc exception



// O(N^2) - Default Constructor
// Pre: N/A
// Post: A gameboard is created with defualt max rows and columns
//       Every cell's status in the game board is set to OPEN.
GameBoard::GameBoard()
{
	maxRows = DEFAULT_ROWS;	// Set max rows to the default amount
	maxCols = DEFAULT_COLS;	// Set max columns to the default amount

	// Create the game board
	AllocateBoard();

}// end DC




// O(N^2) - Non Default Constructor
// Pre: The desired maximum row and column count.
// Post: A gameboard is created with custom max rows and columns
//       Every cell's status in the game board is set to OPEN.
GameBoard::GameBoard(/*IN*/int rows,       // The desired number of rows
					 /*IN*/int cols)	   // The desired number of columns
{
	maxRows = rows;	// Set max rows to the desired amount
	maxCols = cols;	// Set max columns to the desired amount

	// Create the game board
	AllocateBoard();

}// end NDC




// O(N^2) - Copy Constructor
// Pre: The gameboard object to be copied exists
// Post: A deep copy of a desired gameboard object is made
GameBoard::GameBoard(/*IN*/const GameBoard& orig)     // The gameboard to be copied
{
	// Copy the board
	operator=(orig);
}// end CC




// O(N) - Destructor
// Pre: N/A
// Post: The class object is destroyed, and boardPtrArr points to null
GameBoard::~GameBoard()
{
	// Destroy the board
	DeAllocateBoard();

}// end Destructor




// O(1) - Observer Accessor
// Pre: The coordinate of the desired cell
// Post: The status of the cell will be returned if loc is within the bounds of the gameboard.
//       If loc is outside the bounds of the gameboard the status OUT_OF_BOUNDS will be returned
StateEnum GameBoard::GetStatus(/*IN*/const Location2DRec& loc) const  // The desired cell's coordinate
{
	// Check if the cooridnate is within the bounds of the board
	if (loc.x >= ZERO && loc.x < maxRows && loc.y >= ZERO && loc.y < maxCols)
		return boardPtrArr[loc.x][loc.y].status;	// Return the status of the cell

	// Otherwise treat the coordinate as a OUT_OF_BOUNDS
	return OUT_OF_BOUNDS;

}// end GetStatus




// O(1) - Mutator
// Pre: The coordinate of the desired cell
//      The status the cell is to be updated to
// Post: If loc is within the gameboard the status of the desired cell 
//       will be updated to the new status.
//       If loc is outside the gameboard, nothing will occur
void GameBoard::SetStatus(/*IN*/const Location2DRec& loc,      // The desired cell's coordinate
						  /*IN*/ const StateEnum& newStatus)   // The cells new status
{
	// Check if the cooridnate is within the bounds of the board
	if (loc.x >= ZERO && loc.x < maxRows && loc.y >= ZERO && loc.y < maxCols)
		boardPtrArr[loc.x][loc.y].status = newStatus;	// Update the status of the cell

}// end SetStatus




// O(1) - Observer Accessor
// Pre: The board exists
// Post: The size of the board will be stored into the incoming rows and columns variables       
void GameBoard::GetSize(/*OUT*/int& rows,				// The location to store the row size
						/*OUT*/int& cols) const			// The location to store the column size
{
	// Get and store the row and column size
	rows = maxRows;
	cols = maxCols;
}// end GetSize





// O(N^2) - Overloaded Operator
// Pre: The gameboard to be copied
// Post: A deep copy of the gameboard will be created and returned
void GameBoard::operator =(/*IN*/ const GameBoard& orig) // The gameboard to be copied
{

	// Delete the current board
	DeAllocateBoard();

	// Copy the size of the new game board
	maxRows = orig.maxRows;
	maxCols = orig.maxCols;

	// Create the board
	AllocateBoard();

	// Copy each cells status
	for (int i = ZERO; i < maxRows; i++)
		for (int j = ZERO; j < maxCols; j++)
			boardPtrArr[i][j].status = orig.boardPtrArr[i][j].status;

}// end operator =



// ============================ PROTECTED METHODS =================================



// O(N^2)
// Pre: N/A
// Post: The boardPtrArr will be pointing at a dynamic 2D array,
//		 or the board will not be allocated due to not enough heap memory
// Exceptions: GBOutOfMemoryException will be thrown if the heap runs out of memory
void GameBoard::AllocateBoard()
{
	try
	{
		// Create an array of pointers
		boardPtrArr = new CellRec * [maxRows];

		// Iterate through and create an array of size max columns for each pointer
		for (int i = ZERO; i < maxRows; i++)
		{
			// Create the columns for the row
			boardPtrArr[i] = new CellRec[maxCols];

			// Set each cell in that row to OPEN
			for (int j = ZERO; j < maxCols; j++)
				boardPtrArr[i][j].status = OPEN;
		}
	}
	catch (std::bad_alloc)	// The heap space memory has run out
	{
		// Throw the exception
		throw GBOutOfMemoryException();
	}
}// end AllocateBoard




// O(N)
// Pre: The board must be allocated first
// Post: The memory the gameboard is using will be returned to the heap
void GameBoard::DeAllocateBoard()
{
	// Free up any memory that was allocated
	for (int i = ZERO; i < maxRows; i++)
	{
		delete[] boardPtrArr[i];
	}
	// Free the array of pointers
	delete[] boardPtrArr;

	// Set the pointer to null, because why not
	boardPtrArr = nullptr;

}// end DeAllocateBoard
