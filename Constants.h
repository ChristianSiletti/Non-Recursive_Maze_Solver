#pragma once
/*
    FileName : Constants.h
    Author: Christian Siletti
    Date: 3/28/24
    Project Maze

    Purpose: This file contains the constants and enums used in the maze project

*/
#include <string>		// For the string datatype

using namespace std;    // Standard namespace

// Enumerated type to determine direction of travel
enum DirectionEnum { NA, NORTH, EAST, SOUTH, WEST };

// Enum to specify the state a cell is in
enum StateEnum { OPEN, OUT_OF_BOUNDS, VISITED, WALL };


// Struct to contain an x y z position
struct Location2DRec
{
    int x;     // The row position
    int y;     // The column position
};


// Constants
const int DEFAULT_ROWS = 5;         // The default maximum amount of rows
const int DEFAULT_COLS = 5;         // The default maximum amount of columns
const int ZERO = 0;                 // A lower index bound
const int OFFSET = 1;               // Amount to offset a number by one
const int CHAR_AFTER_PERIOD = 3;    // The number of characters after a period for a file name


const Location2DRec START_POS = { 0 , 0 };	// The x and y coordinate of the starting position

const string EXIT_DIR = "S";                // The direction taken to exit the gameboard
const string OUTPUT_FILE = "solution.out";  // The name of the output file