//Implementation File
//Author: Derek Gordon
//Date: November 14, 2011
//Modified: March 28, 2012
//Purpose: To implement the methods specified in the 
//	specification file

#include "exceptions.h"
#include <iostream>



ExceptionClass::ExceptionClass(ExceptionEnum exc)
{

	switch(exc)
	{
	case 0: cout << "List is Empty, Cannot Pop" << endl; break;
	case 1: cout << "List is Empty, Cannot Retrieve" << endl; break;
	default: cout << "An Unknown Error has occurred. Please contact your helpdesk." << endl;
	}//end switch

}

