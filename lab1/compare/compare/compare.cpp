#include "stdafx.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int CompareFiles(const string & fileName1, const string & fileName2, string & error)
{
	char ch1, ch2;
	int currentLine = 1;
	ifstream firstFile(fileName1), secondFile(fileName2);

	if (!firstFile.is_open())
	{	
		error = error.append("Failed to open ").append(fileName1).append(" for reading");
		return -1;
	}

	if (!secondFile.is_open())
	{
		error = error.append("Failed to open ").append(fileName2).append(" for reading");
		return -1;
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
			return currentLine;
		}
	}

	if (firstFile || secondFile)
	{
		return currentLine;
	}	

	return 0;
}

int main(int argc, char * argv[])
{
	string errorMessage = "";
	const int FILE_COMPARISON_ERROR = -1;
	const int FILES_ARE_EQUAL = 0;

	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: compare.exe <input file> <input file>\n";
		return 1;
	}	

	int result = CompareFiles(argv[1], argv[2], errorMessage);

	if (result == FILE_COMPARISON_ERROR)
	{
		cout << errorMessage << "\n";
		return 1;
	}
	else if (result == FILES_ARE_EQUAL)
	{
		cout << "Files are equal!\n";		
	}
	else
	{
		cout << "Files are different. Line number is " << result << "\n";
		return 1;
	}
	
	return 0;
}