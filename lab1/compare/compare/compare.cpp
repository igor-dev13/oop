#include "stdafx.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	ifstream firstFile(argv[1]), secondFile(argv[2]);
	char ch1, ch2;
	int currentLine = 1;

	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: compare.exe <input file> <input file>\n";
		return 1;
	}

	if (!firstFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	if (!secondFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading\n";
		return 1;
	}	

	auto ReadFiles = [&] {
		firstFile.get(ch1);
		secondFile.get(ch2);
		return firstFile && secondFile;
	};
		
	while (ReadFiles())
	{	
		if (ch1 == '\n' && ch2 == '\n')
		{
			++currentLine;
		}

		if (ch1 != ch2)
		{
			cout << "Files are different. Line number is " << currentLine;
			return 1;
		}
	}

	if (firstFile || secondFile)
	{
		cout << "Files are different. Line number is " << currentLine;
		return 1;
	}
	
		
	cout << "Files are equal!\n";
	return 0;
}