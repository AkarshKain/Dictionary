#include<iostream>
#include<fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char **argv)
{
		Dictionary root = Dictionary();
		if(argc != 3)
	    {
            cout<<"wrong number of arguments"<<endl;
            return 1;
        }
        else
        {
            ifstream fileStream1;
			fileStream1.open(argv[2]);
			if (fileStream1.fail()) // file not found
			{
				cout<<"COULD NOT OPEN "<<argv[2]<<endl;
                return 1;
            }
            else
            {
				string line = "";
				const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
                while (getline(fileStream1, line))
				{
					char *line_c = new char [line.length()+1];
					strcpy (line_c, line.c_str());
					char *token = (char*)strtok(line_c, separators); // split the line
					while (token != NULL)
					{
						root.insert(token);
						token = strtok(NULL, separators); // get the next token from the line_c buffer
					}
				}
            }


			ifstream fileStream2;
			fileStream2.open(argv[1]);
			if (fileStream2.fail()) // file not found
			{
				cout<<"COULD NOT OPEN "<<argv[1]<<endl;
                return 1;
            }
            else
            {
				string line = "";
				const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
                while (getline(fileStream2, line))
				{
					char *line_c = new char [line.length()+1];
					strcpy (line_c, line.c_str());
					char *token = (char*)strtok(line_c, separators); // split the line
					while (token != NULL)
					{
						if(root.find(token) == MISSPELLED)  // check the token
							cout<<token<<endl;
						token = strtok(NULL, separators); // get the next token from the line_c buffer
					}
				}
            }
        }

		system("pause");
	return 0;
}