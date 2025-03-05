#pragma once
/*
	FileName : stackrec.h
	Author: Christian Siletti
	Date: 3/30/24
	Project Maze

	Purpose: This file contains the specification for an item to be stored
			 in a stack class.

	ASSUMPTIONS:
		
*/

#include "Constants.h"  // File containing appropriate constants


struct StackRec
{
	Location2DRec loc;	// A x,y coordinate location
	DirectionEnum dir;	// A compass direction or N/A
						// The direction travelled to get to the current location from
						// the stacks previous location
};