//Filename:exception.h
//Author: Luke Musto
//Date: 3.26.2024
//Purpose: File contains exceptions utilized by Stack ADT
// 
//Assumptions:None
// 
//Exceptions Defined:


class OutOfMemoryException
{};
//Thrown on Push when memory is not available. 


class RetrieveOnEmptyException
{};
//Thrown when method Retrieve attempted on Empty ADT.