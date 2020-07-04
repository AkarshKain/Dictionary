#define Nchars 27 /* a-z + ' */

typedef enum {
	CORRECT, // word has correct spelling
	MISSPELLED,
	BADCHARS, // word has characters outside [A-Z,a-z,']
	ADDED,
	EXISTS,
} ResultType;

class Dictionary
{
public :

	bool isEndOfWord;

	Dictionary *next[Nchars];

	int indexOfChar;
	// constructor
	Dictionary()
	{
		for(int i = 0; i < Nchars; i++) // intialize the next char array
		{
			next[i] = nullptr;
		}
		indexOfChar = -1; // intialize the with default value -1 
	}

	ResultType find(const char *word, const char *targetword=nullptr);

	ResultType insert(const char *characters, const char * targetword =nullptr);
};
