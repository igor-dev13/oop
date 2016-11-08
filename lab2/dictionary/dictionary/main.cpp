#include "stdafx.h"
#include "dictionaryProcessor.h"

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
	
	string dictionaryFileInput = argv[1];
	Dictionary dictionary;
	ifstream dictionaryInput(dictionaryFileInput);

	if (dictionaryInput.is_open())
	{
		SerializeDictionary(dictionary, dictionaryInput);
		dictionaryInput.close();
	}
	else
	{
		cout << "Can't process " << dictionaryFileInput << " for open";
	}

	stringstream input;
	ProcessDictionary(dictionary, cin, dictionaryFileInput);

	return 0;
}