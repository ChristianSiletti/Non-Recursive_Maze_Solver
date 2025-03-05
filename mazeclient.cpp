/*
	FileName : mazeclient.cpp
	Author: Christian Siletti
	Date: 3/30/24
	Project Maze

	PURPOSE:
		To read in a gameboard's size and the coordinates of its walls from an input file, 
		and then proceed to find every possible path from one point to another. All paths will
		be labelled and the directions of travel taken to complete each path will be output to an
		output file.

	INPUT:
		The name of the input file will be read in from the user. The first line of the input file 
		will contain the size of the gameboard, all proceeding lines will contain coordinates of the
		walls within the gameboard.

	PROCESSING:
		The file name will be validated, and its existence will be checked.
		Valid gameboard size will be checked as well. The walls of the gameboard will be created,
		and then every possible path within the gameboard will be found.

	OUTPUT:
		If the input file name is invalid the user will be asked to retype the name.
		If the file does not exist or contains an invalid size for the gameboard, an error
		message will appear and the program will abort.
		If the file is found and the size is valid, every possible path will be printed to OUTPUT_FILE.
		The printout will number the paths found and contain the directions travelled within the paths.
		If no paths are found an appropriate output is sent to OUTPUT_FILE.
		The gameboard will be printed to the console screen indicating its walls with X's.
		(IF ENABLED) The maze and the path being searched will be updated to the console screen 
					 in real time.



	ASSUMPTIONS:  ******  IMPORTANT!!!! READ THESE   ******
		1) The size and coordinates within the input file will be integers only,
		   in the format of "x y" per line
		2) A EXIT_DIR movement is made on the exit tile to exit the board
		3) The exit of the board is located in the bottom right corner
		4) The entrance to the board is located at START_POS

	EXCEPTION HANDLING/ERROR CHECKING:
		1) If an invalid file name is given the user must retype the name.
		2) The file will be checked for existance.
		3) The size of the gameboard will be validated as well.
		   (size > 0)




						   SUMMARY OF FUNCTIONS:
	bool ValidateFileName(*IN*string fileName) // The file name being validated
		- Validate a file name
		  (makes sure it contains only letters and a period and 3 letters after the period)
	void ReadWalls(*IN/OUT*GameBoard& board,			// The gameboard whose walls are being set up
				   *IN/OUT*ifstream& fin)				// The input file containing the walls coordinates
		- Read in wall coordinates from an input file and set them up in a gameboard object
	void PrintCurrentPath(*IN*const GameBoard& board,		// The gameboard whose path is being printed
						  *IN*const int& rowSize,			// The boards number of rows
						  *IN*const int& colSize)			// The boards number of columns
		- Print the current path mapped out on the game board
	void PrintCurrentPath(*IN*const GameBoard& board,		// The gameboard whose path is being printed
						  *IN*const Location2DRec& headLoc,	// The location of the head of the path
						  *IN*const int& rowSize,			// The boards number of rows
						  *IN*const int& colSize)			// The boards number of columns
		- Print the current path mapped out on the game board
	DirectionEnum NextDir(*IN*const DirectionEnum& dir)		// The current direction
		- Get the next direction based off a direction sent in (Order: NA -> N -> E -> S -> W -> NA)
	Location2DRec Move(*IN*const DirectionEnum& dir,		// The desired direction to move in
					   *IN*const Location2DRec& currPos)	// The current location
		- Increment a Location2DRec in a single direction
	string PathDirections(*IN* StackClass path)		// The stack containing the path
		- To obtain the directions travelled in a path from start to finish 
*/

#include "stack.h"		// Allows access to the stack ADT
#include "gameboard.h"	// Allows access to the gameboard AD
#include <iostream>		// For console input and output
#include <fstream>		// For input and output file access
#include <thread>		// For the time delay

using namespace std;	// Standard Namespace



// Prototypes
bool ValidateFileName(/*IN*/const string&);	// The file name being validated
void ReadWalls(/*IN/OUT*/GameBoard&,		// The gameboard whose walls are being set up
			   /*IN/OUT*/ifstream&);		// The input file containing the walls coordinates
void PrintCurrentPath(/*IN*/const GameBoard&,			// The gameboard whose path is being printed
					  /*IN*/const int&,					// The boards number of rows
					  /*IN*/const int&);				// The boards number of columns
void PrintCurrentPath(/*IN*/const GameBoard&,			// The gameboard whose path is being printed
					  /*IN*/const Location2DRec&,		// The location of the head of the path
					  /*IN*/const int&,					// The boards number of rows
					  /*IN*/const int&);				// The boards number of columns

DirectionEnum NextDir(/*IN*/const DirectionEnum&);		// The current direction
Location2DRec Move(/*IN*/const DirectionEnum&,			// The desired direction to move in
				   /*IN*/const Location2DRec&);			// The current location
string PathDirections(/*IN*/ StackClass);				// The stack containing the path



void main()
{
	StackClass pathStack;		// The current maze path
	Location2DRec currLoc;		// The current position on the gameboard
	StackRec currItem;			// The item to store within the pathStack
	Location2DRec newLoc;		// The location being analyzed
	DirectionEnum dir = NA;		// The current direction being analyzed
	string inputFile;			// The name of the input file
	ifstream fin;				// The input file reader
	ofstream fout;				// The output file writer
	bool isValid = false;		// Holds if an input file is valid or not
	int pathCt = ZERO;			// The number of valid paths found
	int rows;					// Number of rows in the gameboard
	int cols;					// Number of columns in the gameboard

	
	// Repeats until a valid file name is given
	do
	{
		// Prompt the user for the input file name
		cout << "Please enter the name of the input file: ";

		// Store the users input file name
		cin >> inputFile;

		// Validate the file name
		isValid = ValidateFileName(inputFile);

		// Output an invalid message if needed
		if (!isValid)
		{
			// Output the invalid message
			cout << "\n'" << inputFile << "' is not a valid file name!\n" <<
										  "Please input a different name.\n\n";

			// Pause the screen
			system("pause");
		}

		// Clear the screen
		system("cls");

	} while (!isValid);


	// Open the input file
	fin.open(inputFile);

	// Open the output file
	fout.open(OUTPUT_FILE);		// Open it here so if an error occurs it closes and overwrites itself


	// Checks to see if the file exists
	if (!fin)
	{
		cout << "Error - No File Found!!!" << endl;	// Displays an terminating error message

		// Close the input and output files
		fin.close();
		fout.close();

		abort();	// Abort the program
	}


	// Read in the size of the game board
	fin >> rows;
	fin >> cols;


	// Check if the rows amount and the column amount are valid, abort if not
	if (rows <= ZERO || cols <= ZERO)
	{
		cout << "Error - Invalid Game Board Size!!!" << endl;	// Displays a terminating error message

		// Close the input and output files
		fin.close();
		fout.close();

		abort();	// Abort the program
	}

	// Instantiate a gameboard of custom size
	GameBoard gb(rows, cols);

	// Read in and store the walls in the gameboard
	ReadWalls(gb, fin);

	// Close the input file
	fin.close();


	// Set currLoc temporarily to the exit location
	currLoc.x = rows - OFFSET;
	currLoc.y = cols - OFFSET;

	// Check if the starting position is blocked by a wall
	if (gb.GetStatus(START_POS) == WALL || gb.GetStatus(currLoc) == WALL)
		fout << "No possible paths found!" << endl;

	// If the board is a 1x1 or the start and exit are on the same spot print the only path
	else if (START_POS.x == currLoc.x && START_POS.y == currLoc.y)
		fout << "Path #1: " << EXIT_DIR;	// Print the only path


	// Find every possible path
	else
	{
		// Start at the entrance
		currLoc = START_POS;

		// Store the initial location and direction
		currItem.loc = currLoc;
		currItem.dir = dir;

		// Push the first item onto the stack
		pathStack.Push(currItem);

		// Repeat until the stack is empty
		while (!pathStack.IsEmpty())
		{
			// Get the next direction to search
			dir = NextDir(dir);

			// Get the next coordinate being analyzed
			newLoc = Move(dir, currLoc);

			// See if the space is available to travel into
			if (gb.GetStatus(newLoc) == OPEN)
			{
				// Store the new items information
				currItem.loc = newLoc;
				currItem.dir = dir;

				// Add the new item to the stack
				pathStack.Push(currItem);

				// Set the cell that was just entered to visited
				gb.SetStatus(currLoc, VISITED);

				// Reset the direction to N/A
				dir = NA;

				////	================= CODE TO PRINT THE CURRENT PATH TO OUTPUT =============
				////							(DISABLE IF TOO SLOW) 


				//// Clear the screen
				//system("cls");

				//// Print the path
				//PrintCurrentPath(gb, newLoc, rows, cols);

				//// Add a time delay
				//std::this_thread::sleep_for(50ms);	// I'd make a constant but im not sure what 
				//									// variable that is

				//// =========================================================================

				// Check if the cell is the exit cell
				if (newLoc.x == rows - OFFSET && newLoc.y == cols - OFFSET)
				{

					// Label the path
					fout << "Path #" << ++pathCt << ":\t";

					// Print the path - Exit direction is tacked on as it is the final movement
					fout << PathDirections(pathStack) << "-" << EXIT_DIR << "\n\n";

					// Get the direction of the most recent added item
					dir = pathStack.Retrieve().dir;		// The search will continue from this direction

					// Get rid of the item
					pathStack.Pop();

					// Set the status of the removed cell to open, its no longer appart of the path
					gb.SetStatus(currLoc, OPEN);
				}

				else
					currLoc = newLoc;	// Go to the next location

			}// end if space is open

			// West indicates that a cells direction search has been exhausted so the path must back track
			// until a new direction can be explored
			while (dir == WEST)
			{
				// Get the direction of the most recent added item
				dir = pathStack.Retrieve().dir;		// The search will continue from this direction

				// Get rid of the item, back track the path
				pathStack.Pop();

				// Check to see if the search is over
				if (!pathStack.IsEmpty())
				{
					// Go to the prior location
					currLoc = pathStack.Retrieve().loc;

					// Treat the current location as open until a forward progressing movement is made
					gb.SetStatus(currLoc, OPEN);
				}


				////	================= CODE TO PRINT THE CURRENT PATH TO OUTPUT =============
				////							(DISABLE IF TOO SLOW) 

				//// Clear the screen
				//system("cls");

				//// Print the path
				//PrintCurrentPath(gb, currLoc, rows, cols);

				//// Add a time delay
				//std::this_thread::sleep_for(50ms);	// I'd make a constant but im not sure what
				//									// variable that is

				//// =========================================================================


			}// end while

		}// end while


		// Check if no paths were found
		if (pathCt == ZERO)
			fout << "No possible paths!" << endl;	// Output to the file that no paths were found

	}// end else


	// Close the output file
	fout.close();

	// Clear the screen
	system("cls");

	// Print the emptry board
	PrintCurrentPath(gb, rows, cols);


}// end main




// =========================================== FUNCTIONS ==============================================



// O(N)
// Purpose: Validate a file name
//			(make sure it contains onl letters and a period and 3 letters after the period)
// Pre: The file name
// Post: Returns true if the file name is valid,
//		 otherwise false
bool ValidateFileName(/*IN*/const string& fileName)	// The file name being validated
{
	bool periodFound = false;	// Keeps track of if a period is found or not
	int pos = ZERO;				// Keeps track of the position in the string
	int extenAmt = ZERO;		// Keeps track of the number of extension characters


	// Check if the first character is a period
	if (fileName[pos] == '.')
		return false;	// Return false because a letter is needed before the period


	// Repeat until the end of the string or until a period is found
	while(pos < fileName.length() && !periodFound)
	{
		// See if the character is the period
		if (fileName[pos] == '.')
			periodFound = true;


		// Check if the character is not a letter
		else if (fileName[pos] < 'A' || fileName[pos] > 'z')
			return false;	// Return false if not a letter


		// Increment position
		pos++;
	}

	// If the period is found check for the last three characters
	if (periodFound)
	{
		// Check to see if there are only three letter characters remaining
		while (extenAmt < CHAR_AFTER_PERIOD && pos < fileName.length())
		{
			// Check if the character is not a letter
			if (fileName[pos] < 'A' || fileName[pos] > 'z')
				return false;	// Return false if not a letter

			// Increment pos
			pos++;

			// Increment extenAmt
			extenAmt++;
		}

		// Check if pos is equal to the length of the fileName
		// and that there were only three characters after the period
		if (pos == fileName.length() && extenAmt == CHAR_AFTER_PERIOD)
			return true;	// It is a valid file name

	}

	return false;	// Somewhere along the way the fileName was not valid


}// end ValidateFileName



// ===================================================================================================



// O(N)
// Purpose: Read in wall coordinates from an input file and set them up in a gameboard object
// Pre: The board the walls are being set up in, and the input file with the walls coordinates
// Post: The walls are placed in the appropriate gameboard coordinates,
//		 any invalid or out of range coordinates will be ignored
void ReadWalls(/*IN/OUT*/GameBoard& board,			// The gameboard whose walls are being set up
			   /*IN/OUT*/ifstream& fin)				// The input file containing the walls coordinates
{
	Location2DRec wallCoord;	// Temporary storage for the wall coordinate


	// Grab and store the wall coordinate - priming read
	fin >> wallCoord.x;
	fin >> wallCoord.y;


	// While coordinates are still within the file
	while (fin)
	{
		// Put the wall in the game board
		board.SetStatus(wallCoord, WALL);

		// Grab and store the wall coordinate
		fin >> wallCoord.x;
		fin >> wallCoord.y;

	}// end while

}// end ReadWalls



// ===================================================================================================



// O(N^2)
// Purpose: Print the current path mapped out on the game board
//			Specifying the head position.
// Pre: The game board, the paths head, and its row and column size are needed
// Post: The gameboard will be printed to the console in a table format with green
//		 0's indicating the path, red X's indicating the walls, and a 
//		 green O indicating the head
void PrintCurrentPath(/*IN*/const GameBoard& board,			// The gameboard whose path is being printed
					  /*IN*/const Location2DRec& headLoc,	// The location of the head of the path
					  /*IN*/const int& rowSize,				// The boards number of rows
					  /*IN*/const int& colSize)				// The boards number of columns
{
	StateEnum cellState;	// The current cell's status
	Location2DRec currLoc;	// The current cell's location


	// Prints the board 
	for (int i = ZERO; i < rowSize; i++)
	{
		// Get the current row
		currLoc.x = i;

		// Print the table border
		for (int j = ZERO; j < colSize; j++)
		{
			cout << "+---";	// This will print the appropriate amount of cells
		}
		cout << "+\n";		// Tac on the last corner and go to the next line

		// Print the contents of the cells
		for (int j = ZERO; j < colSize; j++)
		{
			// Get the current column
			currLoc.y = j;

			// Get the status of the cell
			cellState = board.GetStatus(currLoc);

			// Check if the location is the head
			if(currLoc.x == headLoc.x && currLoc.y == headLoc.y)
				cout << "| " << "\033[1;32mO\033[0m" << " ";	// Prints a green O

			else
			{
				// Determine and output the appropriate output
				switch (cellState)
				{
				case WALL: cout << "| " << "\033[1;31mX\033[0m" << " "; break;	// Prints a red X
				case OPEN: cout << "|   "; break;	// Prints a blank cell
				case VISITED: cout << "| " << "\033[1;32m0\033[0m" << " "; break;	// Prints a green 0
				default: break;	// Do nothing
				};
			}

		}

		cout << "|\n";		// Tac on the last border and go to the next line


	}// end row for loop

	// Print the bottom table border
	for (int j = ZERO; j < colSize; j++)
	{
		cout << "+---";	// This will print the appropriate amount of cells
	}
	cout << "+\n";		// Tac on the last corner and go to the next line

}// end PrintCurrentPath



// ===================================================================================================



// O(N^2)
// Purpose: Print the current path mapped out on the game board
// Pre: The game board and its row and column size are needed
// Post: The gameboard will be printed to the console in a table format with green
//		 0's indicating the path, and red X's indicating the walls
void PrintCurrentPath(/*IN*/const GameBoard& board,			// The gameboard whose path is being printed
					  /*IN*/const int& rowSize,				// The boards number of rows
					  /*IN*/const int& colSize)				// The boards number of columns
{
	Location2DRec impLoc;	// Holds an impossible location

	// Set the imposible location (-1,-1)
	impLoc.x = ZERO - OFFSET;
	impLoc.y = ZERO - OFFSET;

	// Print the path
	PrintCurrentPath(board, impLoc, rowSize, colSize);

}// end PrintCurrentPath



// ===================================================================================================



// O(N)
// Purpose: To obtain the directions travelled in a path from start to finish 
//			and store them in a string
// Pre: The stack containing the path
// Post: The directions travelled in the path will be returned in a string 
//		 in the form of direction-direction (S - E - N - E - S)
string PathDirections(/*IN*/ StackClass path)		// The stack containing the path
{
	string strPath = "";	// The series of directions to travel to exit the board

	// Repeat until the path is empty
	while (!path.IsEmpty())
	{
		// Add the direction travelled to the string path
		switch (path.Retrieve().dir)
		{
		case NORTH: strPath = "N-" + strPath;	break;
		case SOUTH: strPath = "S-" + strPath;	break;
		case EAST: strPath = "E-" + strPath;	break;
		case WEST: strPath = "W-" + strPath;	break;
		default: break;
		};

		// Get rid of the current item
		path.Pop();


	}// end while

	// Erase the extra "- " in the back
	strPath.erase(strPath.length() - OFFSET);
	
	// Erase the extra " " at the front
	//strPath.erase(ZERO,OFFSET);

	// Return the string path
	return strPath;

}// end PrintPathDirections



// ===================================================================================================



// O(1)
// Purpose: Get the next direction based off a direction sent in (Order: NA -> N -> E -> S -> W -> NA)
// Pre: The current direction
// Post: The next direction will be returned
DirectionEnum NextDir(/*IN*/const DirectionEnum& dir)		// The current direction
{
	// Return the appropriate direction
	switch (dir)
	{
	case NA: return NORTH;
	case NORTH: return EAST;
	case EAST: return SOUTH;
	case SOUTH: return WEST;
	case WEST: return NA;
	default: return NA;
	};

}// end NextDir



// ===================================================================================================



// O(1)
// Purpose: Increment a Location2DRec in a single direction
// Pre: The desired direction and the Location2DRec being changed
// Post: A Location2DRec will be returned with the new coordinate
//		 If NA or another non compass direction is sent in, the new location will
//		 be the same as the old location
Location2DRec Move(/*IN*/const DirectionEnum& dir,		// The desired direction to move in
				   /*IN*/const Location2DRec& currPos)	// The current location
{
	Location2DRec newPos = currPos;		// The updated location

	// Increment newPos according to the specified direction
	switch (dir)
	{
	case NORTH:
		newPos.x--;
		break;
	case SOUTH:
		newPos.x++;
		break;
	case EAST:
		newPos.y++;
		break;
	case WEST:
		newPos.y--;
		break;
	default:
		break;
	};

	// Return the updated position
	return newPos;

}// end Move




// ========================================== END FUNCTIONS ==========================================


/*											APPENDED OUTPUT
+---+---+---+---+---+---+---+---+---+---+
|   |   |   | X |   |   | X | X | X | X |
+---+---+---+---+---+---+---+---+---+---+
|   | X |   | X | X |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+
|   | X |   | X |   |   | X | X | X |   |
+---+---+---+---+---+---+---+---+---+---+
|   | X |   |   | X |   | X | X |   |   |
+---+---+---+---+---+---+---+---+---+---+
|   |   | X |   |   |   | X | X | X |   |
+---+---+---+---+---+---+---+---+---+---+
|   | X |   | X | X |   | X | X | X |   |
+---+---+---+---+---+---+---+---+---+---+
|   |   | X |   | X |   | X | X | X |   |
+---+---+---+---+---+---+---+---+---+---+
| X |   |   | X | X |   | X | X |   |   |
+---+---+---+---+---+---+---+---+---+---+
|   | X |   |   | X |   | X | X |   | X |
+---+---+---+---+---+---+---+---+---+---+
|   | X | X |   |   |   | X | X |   |   |
+---+---+---+---+---+---+---+---+---+---+
*/