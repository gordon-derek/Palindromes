//Implementation FILE : SnQStaticArray.cpp
//Author: Derek Gordon
//Date: 3/19/2012
//Purpose: To implement the methods of both
//	 a stack and a que class into one class.
//	these methods are declared in the header
//	file and gives the list the ability to
//	be used as a StackClass or a QueClass.
//
//Assumptions:
//	The ItemType passed in by the client will
//	be populated with an intended and valid
//	key.
//
//
//Error Handling:
//	PopDeQ on Empty
//	Retrieve on Empty

#include "snqDynArr.h"
#include <iostream>
using namespace std;

SnQClass::SnQClass()
{
	//initialize all pdm's to their default values
	snq = new ItemType [INITIAL_SIZE];
	front = 0;
	back = 1;
	size = INITIAL_SIZE;
	length = 0;
}//end constructor

/**********************************************************************************************/

SnQClass::~SnQClass()
{
	//delete pointer to the list, returns memory to system
	delete [] snq;
}//end destructor

/**********************************************************************************************/

SnQClass::SnQClass(const SnQClass& orig)
{

	//copy size and list placements
	size = orig.size;
	front = orig.front;
	back = orig.back;
	length = orig.length;

	//set size of list to the same as orig
	snq = new ItemType [size];
	
	//cycle through orig copying items over to same 
	//spot in applying list
	for(int i = 0; i < size; i++)
		snq[i] = orig.snq[i];

}//end copy constructor

/**********************************************************************************************/

bool SnQClass::IsEmpty() const
{
	return (back == (front + 1) % size);
}//end IsEmpty

/**********************************************************************************************/

bool SnQClass::IsFull() const
{
	return (back == front);
}//end IsFull

/**********************************************************************************************/

void SnQClass::EnQ(ItemType newItem)
{
	//list is full, need to expand
	if( IsFull() )
		Expand();

	//insert at back
	snq[back] = newItem;

	//set back to next location
	back = (back + 1) % size;

	length++;

}//end EnQ

/**********************************************************************************************/

void SnQClass::Push(ItemType newItem)
{
	//list is full, need to expand
	if( IsFull() )
		Expand();
		
	//insert at front
	snq[front] = newItem;

	//decrement front for new top of list
	front = (front + size - 1) % size;
	length++;
	

}//end Push

/**********************************************************************************************/

void SnQClass::PopDeQ()
{

	try
	{
		//cannot delete from an empty list
		if(IsEmpty())
			throw ExceptionClass(POP_ON_EMPTY);	

		//if occupancy is less than 25% and larger than initial size
		//contract the list
		if(length == (size * .25) && size != INITIAL_SIZE)
			Contract();

		//increment front for new top of list
		front = (front + 1) % size;
		length--;
	}
	catch(ExceptionClass)
	{}
}//end PopDeQ

/**********************************************************************************************/

ItemType SnQClass::Retrieve() const
{
	try
	{
		//Cannot retrieve from an empty list
		if(IsEmpty())
			throw ExceptionClass(RET_ON_EMPTY);

		return snq[(front + 1) % size];
	}
	catch(ExceptionClass)
	{}
}//end Retrieve

/**********************************************************************************************/

void SnQClass::Clear()
{
	//pop items off list until empty
	while(!IsEmpty())
		PopDeQ();

	//reset front and back to default
	front = 0;
	back = 1;
}//end Clear

/**********************************************************************************************/

void SnQClass::Expand()
{
	SnQClass temp;	//stores list
	
	//temp gets all applying classes pdm's
	temp.snq = snq;
	temp.front = front;
	temp.back = back;
	temp.size = size;

	//size is doubled
	size = size * 2;
	//reinitialize pointer with a larger list
	snq = new ItemType[size];
	//set pdm's to default
	front = 0;
	back = 1;
	length = 0;

	//take all the elements in temp and put them in
	//applying class object
	while(!temp.IsEmpty())
	{
		EnQ(temp.Retrieve());
		temp.PopDeQ();
	}//end while

}//end Expand

/**********************************************************************************************/

void SnQClass::Contract()
{
	SnQClass temp;//stores list
	
	//temp gets all applying classes pdm's
	temp.snq = snq;
	temp.front = front;
	temp.back = back;
	temp.size = size;

	//size is halved
	size = size / 2;
	//reinitialize pointer to smaller list
	snq = new ItemType[size];
	//reset pdm's back to defaults
	front = 0;
	back = 1;
	length = 0;
	
	//take all the elements in temp and put them in
	//applying class object
	while(!temp.IsEmpty())
	{
		EnQ(temp.Retrieve());
		temp.PopDeQ();
	}//end while
}//end Contract

/**********************************************************************************************/

bool SnQClass::operator==(SnQClass rtOp)
{
	//set positions to top of list
	int currPos = (front + 1) % size;
	int rtOpPos = (rtOp.front + 1) % size;

	//sizes must be same to be equal
	if(size != rtOp.size)
		return false;

	//cycle through lists checking item by item
	while(currPos != back && rtOpPos != rtOp.back)
	{
		if(snq[currPos].key != rtOp.snq[rtOpPos].key)
			return false;

		//go to next item down the list
		currPos = (currPos + 1) % size;
		rtOpPos = (rtOpPos + 1) % size;
	}//end while

	return true;
}//end operator==

/**********************************************************************************************/

void SnQClass::operator =(const SnQClass& orig)
{


	//copy size and list placements
	size = orig.size;
	front = orig.front;
	back = orig.back;
	length = orig.length;

	//set size of list to the same as orig
	snq = new ItemType [size];
	
	//cycle through orig copying items over to same 
	//spot in applying list
	for(int i = 0; i < size; i++)
		snq[i] = orig.snq[i];

}//end operator=