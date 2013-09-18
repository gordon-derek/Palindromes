//SPECIFICATION FILE : SnqStaticArray.h
//Author: Derek Gordon
//Date: 3/19/2012
//Purpose: This class will instantiate
//	the properties of both a queue and
//	a stack.  Providing the client with the option
//	to insert on the top or bottom of the stack
//	but deletion will always be achieved by taking
//	the top most item off the stack.


// Assumptions:





//Exception Handling:
// PopDeQ on Empty List
// push on Full List
// EnQ on Full List
// Retrieve on Empty List
// Clear on Empty List




#include "ItemType.h"

int const INITIAL_SIZE = 100;
class SnQClass

{
	public:
	//constructors and destructors
//Pre:
//Post:
//Purpose:
		SnQClass();								///Default Constructor



//SAVE FOR LATER		  
//Pre:
//Post:
//Purpose:
//		~SnQClass();							//Destructor


//Pre
//Post
//Purpose
//		SnQClass(const SnQClass& orig);			//Copy Constructor




	// ADT  operations:
//Pre:
//Post:
//Purpose:

		bool IsEmpty() const;



//Pre:
//Post:
//Purpose:

		bool IsFull() const;



//Pre:snq is NOT full.(IsFull() has been called to check status of snq)
//Post:
//Purpose:

		void EnQ(ItemType newItem);

		
//Pre: snq is NOT full.(IsFull() has been called to check status of snq)
//Post:
//Purpose:

		void Push(ItemType newItem);


//Pre:
//Post:
//Purpose:

		void PopDeQ();



//Pre:snq is NOT EMTPY.(IsEmpty() has been called to check status of snq)
//Post:
//Purpose:
		ItemType Retrieve() const;



//Pre:snq is NOT EMPTY.(IsEmpty() has been called to check status of snq)
//Post:
//Purpose:

		void Clear();


//SAVE FOR LATER
/*
//Pre:
//Post:
//Purpose:  Subtracts elements of RtOp from applying SnQ Class and returns the result;
		virtual SnQClass operator -(const SnQClass& rtOp)const;
			

//Pre:
//Post:
//Purpose:  Copies elements or orig SnQ class into applying class object.
		virtual void operator =(const SnQClass& orig);


*/		


		protected:

		//Pre:SnQ is has no empty spaces for new elements
		//Post:snq has been doubled in size 
		//Purpose:
		void Expand();	



		//Pre:SnQ occupancy is less than or equal to 25%
		//Post:snq has been contracted to 1/2 its previous size
		//Purpose:
		void Contract();	





		
//private data members
	private:       
		ItemType snq[INITIAL_SIZE];			// remember only has size-1 spaces for data... 1 is used for empty front
		int front;
		int back;
		int size;

};  // end SnQClass