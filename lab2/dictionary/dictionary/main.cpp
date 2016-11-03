#include "stdafx.h"
#include "dictionaryMaker.h"

using namespace std;

int main(int argc, char * argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2)
	{
		cout << "Invalid count of arguments\n"
			 << "Usage: dictionary.exe <dictionary file name>\n";
		return 1;
	}
	
	string dictionaryFileIn = argv[1];
	ifstream dictionaryFile(dictionaryFileIn);
	Dictionary dictionary;

	if (dictionaryFile.is_open())
	{
		SerializeDictionary(dictionary, dictionaryFile);
		dictionaryFile.close();
	}
	else
	{
		cout << "Failed to open " << dictionaryFileIn << "for process\n";		
	}

	stringstream input;
	MakeDictionary(dictionary, cin, dictionaryFileIn);

	return 0;
}