//Project: PalinDromes
//FileName: Palindromes.cpp
//Author: Derek Gordon
//Date: 3/18/2012
//Statement of Purpose:
//
//Input: The Filename in which the program will run through to check for word,
//	sentance, line, and full file palindromes.
//
//Processing: The Program will loop through the file on multiple instances to find
//	the type palindrome it is looking for.  One instance for word palindromes, another
//	for sentance so on so fourth.
//
//Output: The file that is being processed is output in a heading alone with every palindrome found
//	along which the amount of characters that make up each palindrome.  The palindromes will be organized
//	into the type that it is.
//
//Error Handling: User input is tested to obey to the rules of the client on filenames. Meaning there is an
//	8 character max on the filename, a period, and a 3 character extension.
//	trying to open an invalid filename(one that does not exist)
//
//Assumptions:
//	The user will abide to the rules by entering a maximum of 8 character filename, a period, and a 3 character
//	extension.
//	The file does have palindromes


#include "snqDynArr.h"	//for use of stack and que class
#include <iostream>		//for screen input/output
#include <string>		//for using string variables
#include <fstream>		//for using file input/output
using namespace std;

//minimum character count to be considered as a palindrome word
const int WORD_MIN = 3;

//Summary Of Methods
bool CheckForValid(const char * str);
//checks the filename to make sure it is valid within the rules
//	defined for file entry in this program.

bool IgnoreChar(/* in */ char entry);
//lists all the characters in which if found in the file are ignored,
//	not inputted into the stack or que.

int WordPal(ifstream& inFile,
			ofstream& outFile);
//checks the entire file for word palindromes, if found they are outputted
// to the outfile and a count is maintained.

int SentancePal( ifstream& inFile,
				ofstream& outFile);
//checks the entire file for sentance palindromes, terminated by a ., if found
// they are outputted to the outfile and a count is maintained

int LinePal( ifstream& inFile,
			 ofstream& outFile);
//checks the entire file, line by line, for palindromes, if found they are outputted
// to the outfile and a count is maintained.

bool FilePal( ifstream & inFile,
			ofstream& outFile);
//checks the entire file as a whole to check if its a palindrome, if decided it is
// it will be outputted to the file.

//stores the ascii value of each valid puncuation mark/special character for comparison
enum ValidCh{ COLON=58,	SEMICOLON=59, QUOTE=39,	DBLQUOTE=34, COMMA=44, PERIOD=46 , FSLASH=47 , QMARK=63 ,
	BKSLASH=92, RSQUIG=125 , LSQUIG=123 , LBRACKET=91, RBRACKET=93, VERTLINE=124, DIAGQUOTE=96, TILDA=126, 
	ATSYMB=64, EXCLAMATION=33,POUND=35, DOLLAR=36, PERCENT=37, CARROT=94, ANDPERSAND=38, ASTERISK=42, LEFTPERAND=40,
	RIGHTPERAND=41, PLUS=43, EQUAL=61, GREATER=62,LESSTHAN=60};	

void main()
{
	ifstream inFile;//used for file input
	ofstream outFile; //used for output
	string fileName;//used for verifying the filename
	int wCt;	//stores amount of word palindromes in file
	int sCt;	//stores amount of sentance palindromes in file
	int lCt;	//stores amount of line palindromes in file
	bool file;	//stores whether the entire file was a palindrome

	cout << "Please input the name of the file you wish to input: ";
	getline(cin, fileName);

	//checks the inserted filename to make sure it is valid
	//if it is not it will ask for a new filename.
	while(!CheckForValid(fileName.c_str()))
	{
		system("cls");//clear screen
		cout << "Filename is not Valid, Please try again" << endl << endl;
		cout << "Please input the name of the file you wish to input: ";
		getline(cin, fileName);
		
	}//end while

	//open the file containing palindromes for reading
	inFile.open(fileName.c_str());
	//check to make sure the file was able to open before reading
	if(!inFile.is_open())
		cout << "There was an error reading the file. Program terminating" << endl;
	else
	{
		//open the output file for writing
		outFile.open("results.dat");

		//output heading line to file
		outFile << "Searching For palindromes in " << fileName << endl << endl;
		
		//Find Word Palindromes >>>
		outFile << "Word Palindromes:" << endl;
		wCt = WordPal(inFile, outFile);
		outFile << wCt << " Word Palindromes." << endl << endl;
		//<<<
		inFile.clear();
		inFile.seekg(0, ios::beg);
		//Find Sentance Palindromes >>>
		outFile << "Sentance Palindromes:" << endl;
		sCt = SentancePal(inFile, outFile);
		outFile << sCt << " Sentance Palindromes." << endl << endl;
		//<<<
		inFile.clear();
		inFile.seekg(0, ios::beg);
		//Find Line Palindromes
		outFile << "Line Palindromes:" << endl;
		lCt = LinePal(inFile, outFile);
		outFile << lCt << " Line Palindromes." << endl << endl;
		//<<<
		inFile.clear();
		inFile.seekg(0, ios::beg);
		//Find Line Palindromes
		outFile << "File Palindromes:" << endl;
		file = FilePal(inFile, outFile);
		outFile << file << " File Palindromes." << endl << endl;
		//<<<

		//output total number of palindromes
		outFile << (wCt + sCt + lCt + (int)file) << " Total Palindromes in this file." << endl;
		
	}//end else
}//end main

/**********************************************************************************************/

//Pre: a filename has been inserted
//Post: whether the filename follows the rules of max 8 character name, a period,
//	and a 3 character extension.
//Purpose: To check the filename to ensure that it is following our rules for
//	filename input.
bool CheckForValid(const char * str)
{
	int ct = 0; //ct after decimal
	int nameCt = 0; //ct of filename
	int decCt = 0;	//amount of decimals in filename

	// is the string empty?
	if (strlen(str) == 0)
		return false;

	while (*str != '\0')
	{
		if(decCt == 0)
		{

			//if there is a decimal, and its first decimal found
			if(*str == '.')
				decCt++;

			else if(nameCt >= 8)
				return false;

			else
				nameCt++;

		}//end if
		else if(decCt == 1)
		{
			//we are now in the extension of the file

			if(ct >= 3)//no more then 3 characters allowed in extension
				return false; //not a valid extension

			if(*str == '.')//second period in extension not allowed
				return false;

			else if(*str > '0' && *str <= '9')//no numbers allowed in filename/extension
				return false;

			ct++;

		}//end else if
		
		str++; // move to next character
	}//end while

	return true; // filename obeyed the rules
}//End CheckForValid

/**********************************************************************************************/

//Pre: entry contains a character
//Post: whether the character is to be ignored or not
//Purpose: to check entry with the list of characters that
//	are to be ignored in processing the file for palindromes
bool IgnoreChar(/* in */ char entry)
{
	int cValue = (int)entry;

	//compare the ascii value of entry to all other valid charactors to ignore
	switch(entry)
	{
	case 58: return true; break;// :
	case 59: return true; break;// ;
	case 39: return true; break;// '
	case 34: return true; break;// "
	case 44: return true; break;// ,
	case 46: return true; break;// .
	case 47: return true; break;// /
	case 63: return true; break;// ?
	case 92: return true; break;// \ 
	case 125: return true;break;// }
	case 123: return true;break;// {
	case 91: return true; break;// [
	case 93: return true; break;// ]
	case 124: return true;break;// |
	case 96: return true; break;// `
	case 126: return true;break;// ~
	case 64: return true; break;// @
	case 33: return true; break;// !
	case 35: return true; break;// #
	case 36: return true; break;// $
	case 37: return true; break;// %
	case 94: return true; break;// ^
	case 38: return true; break;// &
	case 42: return true; break;// *
	case 40: return true; break;// (
	case 41: return true; break;// )
	case 43: return true; break;// +
	case 61: return true; break;// =
	case 62: return true; break;// >
	case 60: return true; break;// <
	}
	return false;
}

/**********************************************************************************************/

//Pre: a file has been inputted and checked to be valid
//Post: a count of the amount of word palindromes in the file is 
//	returned along with all words that are palindromes outputted
//	to the outFile.
//Purpose: to check the entire file for word palindromes.
int WordPal(ifstream& inFile,
			ofstream& outFile)
{
	SnQClass forward;	//stores original word
	SnQClass reverse;	//stores reverse of word
	ItemType newItem;	//stores new item for entry
	char entry;
	int ltrCt = 0; //count of letters in word
	int ct = 0;	//count of word palindromes

	//get the first character
	entry = inFile.get();	//priming read

	//if the character returned is a true character
	while(inFile.good())
	{
		//check entry to see if its a whitespace character(terminates a word)
		if(isspace(entry) == 0)
		{
			//call IgnoreChar to check if its a valid punctuation mark/special character
			if(!IgnoreChar(entry))
			{
				//convert to lowercase for easier comparison
				entry = tolower(entry);
				//enter into both objects, one as a stack one as a que so words get reversed
				newItem.key = entry;
				forward.EnQ(newItem);
				reverse.Push(newItem);

				ltrCt++;
			}//end if

		}//if
		else
		{
			//the word is a palindrome and is longer than the minimum character requirement
			if(forward == reverse && ltrCt >= WORD_MIN)
			{				
				while(!forward.IsEmpty())
				{	//clear the list writing the word to file
					outFile << forward.Retrieve().key;
					forward.PopDeQ();
				}//end while
				outFile << " (" << ltrCt << "c)" << endl;
				ct++;	//increment word count
				reverse.Clear();
			}//end if
			else
			{	//clear the lists
				forward.Clear();
				reverse.Clear();
			}//end else
			ltrCt = 0;
		}//end else
		entry = inFile.get();
	}//end while

	//check if terminating word is correct
	if(forward == reverse && ltrCt >= WORD_MIN)
	{
		while(!forward.IsEmpty())
		{	//clear the list writing the word to file
			outFile << forward.Retrieve().key;
			forward.PopDeQ();
		}//end while
		outFile << " (" << ltrCt << "c)" << endl;
		ct++;
		reverse.Clear();
	}//end if

	return ct;
}//end WordPal

/**********************************************************************************************/

//Pre: a file has been inputted and checked to be valid
//Post: a count of the amount of sentance palindromes in the file is 
//	returned along with all sentances that are palindromes outputted
//	to the outFile.
//Purpose: to check the entire file, sentance by sentance, for any palindromes
int SentancePal( ifstream& inFile,
				ofstream& outFile)
{
	SnQClass forward;	//stores original word
	SnQClass reverse;	//stores reverse of word
	ItemType newItem;	//stores new item for entry
	char entry;
	int ltrCt = 0; //count of letters in word
	int ct = 0;	//count of word palindromes

	//get the first character
	entry = inFile.get();	//priming read

	//if the character returned is valid
	while(inFile.good())
	{
		if(entry != '.')
		{
			//check entry to see if its a whitespace character
			if(isspace(entry) == 0)
			{
				//call IgnoreChar to check if its a valid punctuation mark/special character
				if(!IgnoreChar(entry))
				{
					//convert to lowercase for easier comparison
					entry = tolower(entry);
					//enter into both objects, one as a stack one as a que so words get reversed
					newItem.key = entry;
					forward.EnQ(newItem);
					reverse.Push(newItem);

					ltrCt++;
				}//end if

			}//end if
		}//end if
		else
		{
			//the word is a palindrome and is longer than the minimum character requirement
			if(forward == reverse && ltrCt >= WORD_MIN)
			{
				while(!forward.IsEmpty())
				{	//clear the list writing the word to file
					outFile << forward.Retrieve().key;
					forward.PopDeQ();
				}//end while
				outFile << " (" << ltrCt << "c)" << endl;
				ct++;	//increment word count
				reverse.Clear();
			}//end if
			else
			{	//clear the lists
				forward.Clear();
				reverse.Clear();
			}//end else
			ltrCt = 0;
		}//end else
		entry = inFile.get();
	}//end while

	//check if terminating word is correct
	if(forward == reverse && ltrCt >= WORD_MIN)
	{
		while(!forward.IsEmpty())
		{	//clear the list writing the word to file
			outFile << forward.Retrieve().key;
			forward.PopDeQ();
		}//end while
		outFile << " (" << ltrCt << "c)" << endl;
		ct++;
		reverse.Clear();
	}//end if

	return ct;
}//end SentancePal

/**********************************************************************************************/

//Pre: a file has been inputted and checked to be valid
//Post: a count of the amount of line palindromes in the file is 
//	returned along with all lines that are palindromes outputted
//	to the outFile.
//Purpose: to check the entire file, line by line, for any palindromes
int LinePal(ifstream& inFile,
			ofstream& outFile)
{
	SnQClass forward;	//stores original word
	SnQClass reverse;	//stores reverse of word
	ItemType newItem;	//stores new item for entry
	char entry;
	int ltrCt = 0; //count of letters in word
	int ct = 0;	//count of word palindromes

	//get the first character
	entry = inFile.get();	//priming read

	//if the character returned is valid
	while(inFile.good())
	{
		if(entry != '\n')
		{
			//check entry to see if its a whitespace character
			if(isspace(entry) == 0)
			{
				//call IgnoreChar to check if its a valid punctuation mark/special character
				if(!IgnoreChar(entry))
				{
					//convert to lowercase for easier comparison
					entry = tolower(entry);
					//enter into both objects, one as a stack one as a que so words get reversed
					newItem.key = entry;
					forward.EnQ(newItem);
					reverse.Push(newItem);

					ltrCt++;
				}//end if

			}//end if
		}//end if
		else
		{
			//the word is a palindrome and is longer than the minimum character requirement
			if(forward == reverse && ltrCt >= WORD_MIN)
			{
				while(!forward.IsEmpty())
				{	//clear the list writing the word to file
					outFile << forward.Retrieve().key;
					forward.PopDeQ();
				}//end while
				outFile << " (" << ltrCt << "c)" << endl;
				ct++;	//increment word count
				reverse.Clear();
			}//end if
			else
			{	//clear the lists
				forward.Clear();
				reverse.Clear();
			}//end else
			ltrCt = 0;
		}//end else
		entry = inFile.get();
	}//end while

	//check if terminating word is correct
	if(forward == reverse && ltrCt >= WORD_MIN)
	{
		while(!forward.IsEmpty())
		{	//clear the list writing the word to file
			outFile << forward.Retrieve().key;
			forward.PopDeQ();
		}//end while
		outFile << " (" << ltrCt << "c)" << endl;
		ct++;
		reverse.Clear();
	}//end if

	return ct;
}//end LinePal

/**********************************************************************************************/

//Pre: a file has been inputted and checked to be valid
//Post: whether the file is indeed a palindrome or not is
//	returned. If true, the file is outputted to the outFile.
//Purpose: to check if the entire file itself is one palindrome.
bool FilePal(ifstream& inFile,
			ofstream& outFile)
{
	SnQClass forward;	//stores original word
	SnQClass reverse;	//stores reverse of word
	ItemType newItem;	//stores new item for entry
	char entry;
	int ltrCt = 0; //count of letters in word
	int ct = 0;	//count of word palindromes

	//get the first character
	entry = inFile.get();	//priming read

	//if the character returned is valid
	while(inFile.good())
	{
		//check entry to see if its a whitespace character
		if(isspace(entry) == 0)
		{
			//call IgnoreChar to check if its a valid punctuation mark/special character
			if(!IgnoreChar(entry))
			{
				//convert to lowercase for easier comparison
				entry = tolower(entry);
				//enter into both objects, one as a stack one as a que so words get reversed
				newItem.key = entry;
				forward.EnQ(newItem);
				reverse.Push(newItem);

				ltrCt++;
			}//end if

		}//end if
		entry = inFile.get();
	}//end while

	//check if terminating word is correct
	if(forward == reverse && ltrCt >= WORD_MIN)
	{
		while(!forward.IsEmpty())
		{	//clear the list writing the word to file
			outFile << forward.Retrieve().key;
			forward.PopDeQ();
		}//end while
		outFile << " (" << ltrCt << "c)" << endl;
		reverse.Clear();
		return true;
	}//end if

	return false;
}//end FilePal