#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <bitset>
#include "rotatebyte.h"

using namespace std;

const int BITE_ROTATE_ERROR = -1;

int RotateNumber(const string & inputValue1, const string & inputValue2, char * inputValue3, string & error)
{		
	char direction = inputValue3[0];
	
	int number = atoi(inputValue1.c_str());
	int rotationCount = atoi(inputValue2.c_str());

	if (number == 0)
	{
		error = error.append("Enter a valid integer number for <bite>");
		return -1;
	}

	if (rotationCount == 0)
	{
		error = error.append("Enter a valid integer number for  <number of bits>");
		return -1;
	}


	if (direction != 'R' && direction != 'L')
	{
		error = error.append("Enter a valid direction, uppercase - L for left, or R for right");
		return -1;
	}

	if (number > 255 || number < -255)
	{
		error = error.append("bite number range is from -255 to 255");
		return -1;
	}

	if (rotationCount > 8 || rotationCount < 0)
	{
		error = error.append("bit count in bite is is from 0 to 8");
		return -1;
	}

	for (int i = 0; i < rotationCount; i++)
	{
		number = (direction == 'R') ? number >> 1 : number << 1;
	}
	
	return number;
}

int main(int argc, char * argv[])
{
	string errorMessage = "";

	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return 1;
	}	

	int result = RotateNumber(argv[1], argv[2], argv[3], errorMessage);

	if (result == BITE_ROTATE_ERROR)
	{
		cout << errorMessage << "\n";
		return 1;
	}
	else
	{
		cout << result;
	}

	return 0;
}

