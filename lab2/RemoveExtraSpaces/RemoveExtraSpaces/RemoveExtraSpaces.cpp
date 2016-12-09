// RemoveExtraSpaces.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

string RemoveExtraSpaces(const string & fileName1, string & error)
{
	char ch;
	string result;
	ifstream firstFile(fileName1);

	auto ReadFiles = [&] {
		firstFile.get(ch);
		return firstFile;
	};

	while (ReadFiles())
	{
		if (ch == ' ')
		{
			continue;
		}

		result += ch;
	}
}

int main(char *argv[])
{
	string errorMessage = "";

	string result = RemoveExtraSpaces(argv[0], errorMessage);




    return 0;
}

