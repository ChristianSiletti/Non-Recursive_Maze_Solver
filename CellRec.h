#pragma once
/*
	FileName : Cellrec.h
	Author: Christian Siletti
	Date: 3/28/24
	Project Maze

	Purpose: This file contains the specification for an item to be stored
			 in a gameboard class cell.

	ASSUMPTIONS:
		1) StateEnum will have at least two values, OPEN and OUT_OF_BOUNDS
		2) The CellRec will have as a parameter a StateEnum called status
		3) A typdef CellRec** named Board will also be here
*/

#include "Constants.h"  // File containing appropriate constants


// Struct to be stored in the gameboard
struct CellRec
{
	StateEnum status;	// Gives the current status of the cell
};


typedef CellRec** Board;	// The gameboard itself, used to manage the cells