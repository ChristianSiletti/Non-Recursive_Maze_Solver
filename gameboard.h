#pragma once
/*
    FileName : gameboard.h
    Author: Christian Siletti
    Date: 3/28/24
    Project Maze

    PURPOSE:
        Contains the specifications for a GameBoard Class. The struct definition for the
        gameboard's cells should be placed in the file CellRec.h.


    ASSUMPTIONS:  ******   IMPORTANT!!!! READ THESE   ******
        1) The definition of the struct CellRec will be supplied by the client
           in a file called CellRec.h.
        2) The struct will contain a parameter of type StatusEnum called status.
           The StatusEnum will have at least two values OPEN and OUT_OF_BOUNDS.
        3) CellRec.h must contain a typedef CellRec* pointer named Board.
        4) A typdef CellRec** named Board will be defined in CellRec.h as well
        5) If there is not enough space to allocate a board the board will 
           be deleted thus deallocate itself


    EXCEPTION HANDLING/ERROR CHECKING:
        1) If an invalid location is sent into GetStatus a OUT_OF_BOUNDS status will be returned.
        2) If an invalid location is sent into SetStatus the status of the location will not change,
           the program will move on.
        3) GBOutOfMemoryException thrown when memory from the heap has run out


                           SUMMARY OF METHODS:
    PUBLIC METHODS
        GameBoard() - Instantiate a gameboard object with default values
        GameBoard(*IN*int rows,  // The desired number of rows
                  *IN*int cols)  // The desired number of columns
                    - Instantiate a gameboard object with non default values
        GameBoard(*IN*const GameBoard& orig)  // The gameboard to be copied
                    - Performs a deep copy of another gameboard object
        ~GameBoard() - Destroy the class object
        virtual StateEnum GetStatus(*IN*const Location2DRec& loc) const // The desired cell's coordinate
                    - To return the status of a specified cell
        virtual void SetStatus(*IN*const Location2DRec& loc,      // The desired cell's coordinate
                               *IN* const StateEnum& newStatus);  // The cells new status
                    - To change the status of a desired location
        virtual void GetSize(*OUT*int& rows,              // The location to store the row size
                             *OUT*int& cols) const;       // The location to store the column size
                    - To return the size of the board
        virtual void operator =(*IN* const GameBoard& orig); // The gameboard to be copied
                    - To create a deep copy of another gameboard

    PROTECTED METHODS
        virtual void AllocateBoard() - To allocate dynamic memory for a game board object
        virtual void DeAllocateBoard() - To deallocate memory of a game board object


    PRIVATE MEMBERS:
        int maxRows;        // The maximum number of rows
        int maxCols;        // The maximum number of cols
        Gameboard board;    // The gameboard containing every cell's information

*/


#include "Cellrec.h"	// SUPPLIED BY THE CLIENT
// Header which contains details of the cell record
#include "Constants.h"  // File containing appropriate constants
#include "gbExceptions.h"  // Header containing the exception cases/classes

using namespace std;    // Standard namespace



class GameBoard
{
public:

    // O(N^2) - Default Constructor
    // Purpose: Instantiate a gameboard object with default values
    // Pre: N/A
    // Post: A gameboard is created with defualt max rows and columns
    //       Every cell's status in the game board is set to OPEN.
    GameBoard();



    // O(N^2) - Non Default Constructor
    // Purpose: Instantiate a gameboard object with non default values
    // Pre: The desired maximum row and column count.
    // Post: A gameboard is created with custom max rows and columns
    //       Every cell's status in the game board is set to OPEN.
    GameBoard(/*IN*/int rows,       // The desired number of rows
              /*IN*/int cols);      // The desired number of columns



    // O(N^2) - Copy Constructor
    // Purpose: Performs a deep copy of another gameboard object
    // Pre: The gameboard object to be copied exists
    // Post: A deep copy of a desired gameboard object is made
    GameBoard(/*IN*/const GameBoard& orig);     // The gameboard to be copied



    // O(N) - Destructor
    // Purpose: Destroy the class object
    // Pre: N/A
    // Post: The class object is destroyed, and boardPtrArr points to null
    ~GameBoard();



    // O(1) - Observer Accessor
    // Purpose: To return the status of a specified cell
    // Pre: The coordinate of the desired cell
    // Post: The status of the cell will be returned if loc is within the bounds of the gameboard.
    //       If loc is outside the bounds of the gameboard the status OUT_OF_BOUNDS will be returned
    virtual StateEnum GetStatus(/*IN*/const Location2DRec& loc) const;  // The desired cell's coordinate



    // O(1) - Mutator
    // Purpose: To change the status of a desired location
    // Pre: The coordinate of the desired cell
    //      The status the cell is to be updated to
    // Post: If loc is within the gameboard the status of the desired cell 
    //       will be updated to the new status.
    //       If loc is outside the gameboard nothing will occur
    virtual void SetStatus(/*IN*/const Location2DRec& loc,      // The desired cell's coordinate
                           /*IN*/ const StateEnum& newStatus);  // The cells new status 



    // O(1) - Observer Accessor
    // Purpose: To return the size of the board
    // Pre: The board exists
    // Post: The size of the board will be stored into the incoming rows and columns variables       
    virtual void GetSize(/*OUT*/int& rows,              // The location to store the row size
                         /*OUT*/int& cols) const;       // The location to store the column size



    // O(N^2) - Overloaded Operator
    // Purpose: To create a deep copy of another gameboard
    // Pre: The gameboard to be copied
    // Post: A deep copy of the gameboard will be created and returned
    virtual void operator =(/*IN*/ const GameBoard& orig); // The gameboard to be copied


protected:

    // O(N^2)
    // Purpose: To allocate dynamic memory for a game board object
    // Pre: N/A
    // Post: The boardPtrArr will be pointing at a dynamic 2D array,
    //		 or the board will not be allocated due to not enough heap memory
    // Exceptions: GBOutOfMemoryException will be thrown if the heap runs out of memory
    virtual void AllocateBoard();



    // O(N)
    // Purpose: To deallocate memory of a game board object
    // Pre: The board must be allocated first
    // Post: The memory the gameboard is using will be returned to the heap
    virtual void DeAllocateBoard();



private:
    int maxRows;    // The maximum number of rows
    int maxCols;    // The maximum number of cols

    Board boardPtrArr;    // The gameboard containing every cell's information

};