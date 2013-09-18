//Specification File
//Author: Derek Gordon
//Date: November 14, 2011
//Modified: March 28,2012
//Purpose: To handle an exception that
//	is thrown by another class. The
//	exception will be inputted as an
//	enumerated data type and will be handled
//	within the default constructor.
//
//Assumptions:
//	The paramater passed into the class is
//	contained in ExceptionEnum, if not an
//	unknown error exception is outputted.

#include <string>
using namespace std;

enum ExceptionEnum{ POP_ON_EMPTY, RET_ON_EMPTY};
class ExceptionClass
{
public:
		ExceptionClass(ExceptionEnum exc);//default constructor, does nothing

private:

};//end ExceptionClass
	