#include "Dictionary.h"
#include <ctype.h>
#include <string>

using namespace std;

char chars [] = {'a' , 'b' , 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i' , 'j' , 'k' , 'l' , 'm' 
	, 'n' , 'o' , 'p' , 'q' , 'r' , 's' , 't' , 'u' , 'v' , 'w' , 'x' , 'y' , 'z' , '\''};

int getCharIndex(char ch)
{
	// get the index
	for(int i = 0; i < 27; i++)
		if(ch == chars[i])
			return i;
}

char* getRemainingPortion(const char* token)
{
	string s = token;
	s.erase(0, 1);
	char *remainingPortion = new char [s.length()+1];
	strcpy (remainingPortion, s.c_str());
	return remainingPortion;
}

ResultType Dictionary::find(const char *word, const char *targetword)
{
	if(!isalpha(word[0]) && word[0] != '\'')
		return BADCHARS; // bad char

	for(int i = 0; i < Nchars; i++) // find the char that matches the first char in the word
		if(next[i] != nullptr)
		{
			if(next[i]->indexOfChar == getCharIndex(tolower(word[0]))) // if this index of char of the word is same as the index of next[0]
			{
				if(strlen(word) == 1 && !next[i]->isEndOfWord) // if the last char in the word not the end of the word in the dictionary
					return MISSPELLED;
				else
				{
					//create new array of chars for the remaining portion of the word
					const int newSize = strlen(word) - 1;  // new size
					char *remainingPortion = getRemainingPortion(word);
					ResultType rt = next[i]->find(remainingPortion); // recurrsive call for find function
					delete remainingPortion; // release the resource after using it
					return rt; // return the result
				}
			}
		}
		else
			break;

	return MISSPELLED; // not found
}



ResultType Dictionary::insert(const char *characters, const char * targetword)
{
	if(find(characters) == CORRECT)
		return EXISTS;
	else if(find(characters) == MISSPELLED)
	{
		for(int i = 0; i < Nchars; i++) // find the char that matches the first char in the word
			if(next[i] != nullptr)
			{
				if(next[i]->indexOfChar == getCharIndex(tolower(characters[0]))) // if this index of char of the word is same as the index of next[0]
				{
					//create new array of chars for the remaining portion of the word
					const int newSize = strlen(characters) - 1;  // new size
					char *remainingPortion = getRemainingPortion(characters); // get remaining portion
					next[i]->insert(remainingPortion); // recurrsive call for find function
					return ADDED;
				}
			}
			else 
				break; // exit the loop if the first part of new word not exists

		for(int j = 0; j < Nchars; j++)
		{
			if(next[j] == nullptr) // add new chars not exists
			{
				next[j] = new Dictionary();
				next[j]->indexOfChar = getCharIndex(characters[0]);
				const int newSize = strlen(characters) - 1;  // new size
				if(newSize == 0)
				{
					next[j]->isEndOfWord = true; // set the end of the word
					return ADDED;
				}
				char *remainingPortion = getRemainingPortion(characters);
				next[j]->insert(remainingPortion);
				next[j]->isEndOfWord = false;
				return ADDED;
			}
		}
	}
	else
	{
		return BADCHARS;
	}
}



