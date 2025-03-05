//IMPLEMENTATION FILE : stack.cpp
// This file contains the implementation of a dynamically allocated stack.
#include "stack.h"

//***************************************************************************
//*																			*
//*				declare struct from forward declaration						*
//*																			*
//***************************************************************************


struct node
{
	StackRec data;  //data to store
	node* next;     //internal pointer
};



//***************************************************************************
//*																			*
//*				constructors, destructor, and copy constructor				*
//*																			*
//***************************************************************************


//constructor
//Pre: Object has been instantiated
//Post:Stack has been initialized 
StackClass::StackClass()
{

	head = nullptr;  //initialize stack

}  // end default constructor



//copy constructor
//Pre:  orig contains stack to be copied
//Post: a deep copy of orig has been made
StackClass::StackClass(const StackClass& orig)
{
	head = nullptr;		//initialize stack	

	operator=(orig);	//perform deep copy

} // end copy constructor



//destructor
//Pre: Stack exists
//Post: Memory has been returned to the system
StackClass::~StackClass()
{
	Clear();		//return memory to heap

}//end destructor



//***************************************************************************
//*																			*
//*				observer predicators										*
//*																			*
//***************************************************************************


//Pre: Object has been instantiated
//Post: If stack is empty, true is returned. false otherwise. 
bool StackClass::IsEmpty() const
{

	return (head == nullptr);	 

}  // end IsEmpty



//Pre:Object has been instantiated
//Post: If stack is full, true is returned, false otherwise. 
bool StackClass::IsFull() const
{

	return false;

} // end IsFull



//***************************************************************************
//*																			*
//*				observer accessor											*
//*																			*
//***************************************************************************


//Pre: Stack is not empty
//Post: Item at top of stack has been returned
//Exceptions Thrown: RetreiveOnEmptyException()
StackRec StackClass::Retrieve() const
{
	if (!IsEmpty())	
		return head->data;	//return data
	else
		throw RetrieveOnEmptyException();	//stack is empty

}  // end Retrieve



//***************************************************************************
//*																			*
//*							Mutators										*
//*																			*
//***************************************************************************


//Pre: StackRec contains item to be inserted
//Post: newItem is added at the top of the stack 
void StackClass::Push(/*in*/StackRec newItem)  // item to be added
{

	node* temp = Allocate();	//create node
	temp->data = newItem;		//set internal ptr to null
	temp->next = head;			// connect
	head = temp;				//move head

}// end Push



//Pre: Object is instantiated
//Post:  Object at top of the stack has been removed.  If Empty, no changes are made 
void StackClass::Pop()
{
	if (!IsEmpty())				//if not empty
	{
		node* temp = head->next;	//set temp
		delete head;				//delete node
		head = temp;				//reconnect
	}

}  // end Pop



//Pre: Stack  exists
//Post: Stack has been cleared
void StackClass::Clear()
{
	while (!IsEmpty())	//while stack has elememts
		Pop();				//remove them

}  //end Clear



//***************************************************************************
//*																			*
//*					Overloaded Operators									*
//*																			*
//***************************************************************************


//Pre: Stack exists and orig contains element to be copied
//Post: A deep copy of the stack has been made
void StackClass::operator =(const StackClass& orig)
{
	
	// Temporary pointer to start at the head of the original
	node* orgTemp = orig.head;
	// Temporary point to point to add to the new stack
	node* temp;

	// Get rid of anything in the current stack
	Clear();

	// Set head to nullptr just in case
	head = nullptr;

	// See if orgTemp is equal to nullptr
	if (orgTemp != nullptr)
	{
		head = Allocate();	// Create space for the item

		// Go to the start of the new stack
		temp = head;

		// Store the data
		temp->data = orgTemp->data;

		// Repeat until the end of the list
		while (orgTemp->next != nullptr)
		{

			// Allocate space for the next item
			temp->next = Allocate();

			// Move temp and orgTemp
			temp = temp->next;
			orgTemp = orgTemp->next;

			// Store the data
			temp->data = orgTemp->data;
		}
		
		// Set the tail to nullptr
		temp->next = nullptr;

	}// end if



} // end operator = 



//protected method

//Pre:  Object has been instantiated
//Post: If space available, node is allocated and pointer to node is returned
//Exceptions Thrown: OutOfMemoryException()
node* StackClass::Allocate()
{
	try
	{
		node* tbr = new node;	//get a node
		tbr->next = nullptr;	//set internal to null
		return tbr;				//return it

	}

	catch (std::bad_alloc)
	{
		//if memory can not be allocated
		throw OutOfMemoryException();
	}
}	//end Allocate


