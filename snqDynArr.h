//SPECIFICATION FILE : SnQ.h
//Author: Derek Gordon
//Date: 3/18/2012
//Purpose: This file declares the methods used
//	in the use of a stack n que class or DeQue.
//	It allows the client to have the ability to
//	push on to a stack and then EnQ an object to
//	the end of the list which changes the properties
//	of the list or to just have multiple instantiations
//	of a list each with its on property of a standalone
//	stack or que class.
//
// Assumptions:
//	Push refers to the stack class and follows a Last in First Out
//	procedure where EnQ refers to the Que class properties and follows
//	a First in First Out procedure.
//
//Exception Handling:
//	PopDeQ on Empty
//	Retrieve on Empty

//**********Summary of Methods*******************************************
//																		*
//	SnQClass();								///Default Constructor		*
//	-creates the class object, setting pdm's to default values			*
//																		*
//	~SnQClass();							//Destructor				*
//	-returns the memory used by the class object back to memory			*
//																		*
//	SnQClass(const SnQClass& orig);			//Copy Constructor			*
//	-performs a deep copy of orig and stores in applying class object	*
//																		*
//	bool IsEmpty() const;												*
//	-checks the list to see if it is empty or not						*
//																		*
//	bool IsFull() const;												*
//	-checks the list to see if it is full or not						*
//																		*
//	void EnQ(ItemType newItem);	//item to be inserted					*
//	-inserts newItem at the bottom of the list							*
//																		*
//	void Push(ItemType newItem); //item to be inserted					*
//	-inserts newItem at the top of the list								*
//																		*
//	void PopDeQ();														*
//	-deletes the item that is on the top of the list					*
//																		*
//	ItemType Retrieve() const;											*
//	-returns the top item in the list									*
//																		*
//	void Clear();														*
//	-deletes all the items in the list, restoring pdm's					*
//		to default values												*
//																		*
//	virtual bool operator ==(SnQClass rtOp);							*
//	-checks rtOp against the applying class object for equality,		*
//		checks every item in the list.									*
//																		*
//	virtual void operator =(const SnQClass& orig);						*
//	-copies orig to the applying class object.							*
//																		*
//	void Expand();														*
//	-doubles the size of the list so it can fit more items.				*
//																		*
//	void Contract();													*
//	-cuts the size of the list in half due to occupancy under 25%		*
//***********************************************************************


#include "ItemType.h"
#include "exceptions.h"

int const INITIAL_SIZE = 4;
class SnQClass

{
	public:
	//constructors and destructors
//Pre: list is instantiated
//Post: the pdm's are set to their default values
//Purpose: initialize the list and set pdm's to default values
		SnQClass();								///Default Constructor



	  
//Pre: list does exist
//Post: the list is deleted and memory returned to the system
//Purpose: to return the memory that was in use by the class to the system
		~SnQClass();							//Destructor


//Pre: list exists
//Post: a deep copy of the list is created
//Purpose: to create a deep copy of the list.
		SnQClass(const SnQClass& orig);			//Copy Constructor




	// ADT  operations:
//Pre: list exists
//Post: true if the lists has no items, false otherwise
//Purpose: to return whether the list has items or not

		bool IsEmpty() const;



//Pre: list exists
//Post: true if the list is full, false otherwise
//Purpose: to return whether the list is full or not

		bool IsFull() const;



//Pre: snq is NOT full.(IsFull() has been called to check status of snq)
//Post: a new item is inserted at the bottom of the list, back is incremented
//Purpose: to insert a new item at the bottom of the list

		void EnQ(ItemType newItem);	//item to be inserted

		
//Pre: snq is NOT full.(IsFull() has been called to check status of snq)
//Post: a new item is inserted at the top of the list, front is decremented
//Purpose: to insert a new item at the top of the list

		void Push(ItemType newItem); //item to be inserted


//Pre: list exists
//Post: the top item in the list is removed from the list, front is incremented
//Purpose: to remove the top item in the list

		void PopDeQ();



//Pre:snq is NOT EMTPY.(IsEmpty() has been called to check status of snq)
//Post: the top item in the list is returned
//Purpose: to get the top item in the list and return it
		ItemType Retrieve() const;



//Pre:snq is NOT EMPTY.(IsEmpty() has been called to check status of snq)
//Post: all items in the list are deleted, pdm's are returned to default values
//Purpose: to remove all items in the list, reset the list back to defaults

		void Clear();


//SAVE FOR LATER

//Pre: two lists exist
//Post: if all the elements in the list are the same, true is returned
//Purpose: checks to see if the lists are equal, if not returns false
		virtual bool operator ==(SnQClass rtOp);
			

//Pre: two lists exist
//Post: all the elements of orig are copied into the applying class object
//Purpose:  Copies elements of orig SnQ class into applying class object.
		virtual void operator =(const SnQClass& orig);


	


		protected:

		//Pre:SnQ is has no empty spaces for new elements
		//Post:snq has been doubled in size 
		//Purpose: to double the list so that it can hold more elements
		void Expand();	



		//Pre:SnQ occupancy is less than or equal to 25%
		//Post:snq has been contracted to 1/2 its previous size
		//Purpose: to shirnk the list so that we preserve memory
		void Contract();	





		
//private data members
	private:       
		ItemType* snq;			// remember only has size-1 spaces for data... 1 is used for empty front
		int front;				//top of list, always empty
		int back;				//bottom of list
		int size;				//current size of list for expansion/contraction
		int length;				//amount of elements currently in list

};  // end SnQClass