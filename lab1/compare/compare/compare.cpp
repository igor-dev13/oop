#include "stdafx.h"

#include <fstream>
#include <iostream>

using namespace std;

char ch, ch1;
int currentLine = 0;

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: compare.exe <input file> <input file>\n";
		return 1;
	}

	ifstream inputFirst(argv[1]);
	ifstream inputSecond(argv[2]);

	if (!inputFirst.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	if (!inputSecond.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading\n";
		return 1;
	}	

	while (inputFirst.get(ch) && inputSecond.get(ch1))
	{
		if (ch == '\n')
		{
			currentLine = currentLine + 1;
		}

		if (ch != ch1)
		{
			cout << "Files are different. Line number is " << currentLine;
			return 1;
		}
	}
	
	cout << "Files are equal!\n";
	return 0;
}