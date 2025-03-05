///Filename : stack.h
//Specification File : StackClass
//Purpose: This file contains the definition of a dynamic array based StackClass.
//  It is a class template. This allows the class to receive as a parameter
//	the type of data (inherent or user-defined) which the stack is to hold.
// 
// Assumptions: 
//			(1) ADT will be accessible in LIFO method of access only.
// 
// Exceptions Thrown:
//		(1)	Method Retrieve throws a  RetrieveOnEmptyException when retrieve is  
//			attempted from an empty stack.
//		(2) Method Push throws an OutOfmemory Exception on a bad_alloc.
//
//***************************************************************************
//  The public methods are: 
//    StackClass();  		: prepares stack for usage.	
//
//	  ~StackClass();    	: returns all dynamically allocated memory to heap	
//
//	  StackClass(const StackClass& orig);  : creates a deep copy of the class object 	
//		
//    bool IsEmpty() const : returns true if stack has no elements. 
//
//    bool IsFull() const  : returns true if stack has no empty spaces.
//
//    void Push(StackRec newItem);	adds newItem to top of stack
//
//    void Pop();		Removes top item from stack.
//
//    StackRec Retrieve() const;  returns item at top of stack		
//	
//	  void Clear();     Clears the stack   
//
//	  virtual void operator=(const StackClass& orig); Overloads = operator for class object
//
//	  protected methods:
//
//	  node* Allocate();   Allocates a stack object, if memory unavailable, throws out 
//							of memory exception
//***************************************************************************

#include <cstdlib>					//for NULL
#include <new>
#include "stackrec.h"
#include "exception.h"
//forward declaration of struct

struct node;

//class declaration
class StackClass

{
public:

	//constructors and destructors
	//Pre: Object has been instantiated
	//Post:Stack has been initialized  
	//Purpose:  Initialize stack.
	StackClass();  		// default constructor O(1)


	//Pre: Stack exists
	//Post: Memory has been returned to the system
	//Purpose: Return memory to system
	~StackClass();		//destructor	O(N)


	//Pre:  orig contains stack to be copied
	//Post: a deep copy of orig has been made
	//Purpose: to provide a deep copy of a StackClass object
	StackClass(/*in*/const StackClass& orig);	//stack to be copied
												//copy constructor	O(N)  



	// 	ADT stack operations:


	//Pre: Object has been instantiated
	//Post: If stack is empty, true is returned. false otherwise. 
	//Purpose: Determine if stack is empty
	bool IsEmpty() const;      // observer-predicator   O(1)


	//Pre:Object has been instantiated
	//Post: If stack is full, true is returned, false otherwise. 
	//Purpose: Determine if stack is full 
	bool IsFull() const;	  //observer-predicator  O(1)


	//Pre: StackRec contains item to be inserted
	//Post: newItem is added at the top of the stack 
	//Purpose: Adds element newItem to stack
	void Push(/*in*/StackRec newItem);		//item to add 
											// mutator    O(1)


	//Pre: Object is instantiated
	//Post:  Object at top of the stack has been removed.  If Empty, no changes are made 
	//Purpose: Removes top element from stack
	void Pop();		//mutator     O(1)	



	//Pre: Stack is not empty
	//Post: Item at top of stack has been returned
	//Purpose : returns item at top of stack.
	//Exceptions Thrown: RetreiveOnEmptyException()
	StackRec Retrieve() const;	      //observer accessor   O(1)



	//Pre: Stack  exists
	//Post: Stack has been cleared
	//Purpose: To clear the stack
	void Clear();			//mutator/iterator    O(N)


	//overloaded operators
	//Pre: Stack exists and orig contains element to be copied
	//Post: A deep copy of the stack has been made
	//Purpose:  To create a deep copy of a StackClass object
	virtual void operator =(/*in*/const StackClass& orig);  //stack to copy   
															//mutator        O(N)



private:  //pdms
	
	node* head;		//top of stack


protected:
	//Pre:  Object has been instantiated
	//Post: If space available, node is allocated and pointer to node is returned
	//Purpose: Allocates a node with next ptr set to null
	//Exceptions Thrown: OutOfMemoryException()
	node* Allocate();		//O(1)


};  // end StackClass
