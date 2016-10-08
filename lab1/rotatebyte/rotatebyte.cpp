#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <bitset>
#include "rotatebyte.h"

using namespace std;

int RotateNumber(int number, int rotationCount, char direction)
{	
	for (int i = 0; i < rotationCount; i++)
	{
		number = (direction == 'R') ? number >> 1 : number << 1;
	}
	
	return number;
}

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return 1;
	}

	string inputNumber = argv[1];
	string inputCount = argv[2];
	char * direction = argv[3];
	int number = atoi(inputNumber.c_str());
	int rotationCount = atoi(inputCount.c_str());

	if (number == 0)
	{
		cout << "Enter a valid integer number for <bite>\n";
		return 1;
	}

	if (rotationCount == 0)
	{
		cout << "Enter a valid integer number for  <number of bits>\n";
		return 1;
	}


	if (*direction != 'R' && *direction != 'L')
	{
		cout << "Enter a valid direction, uppercase - L for left, or R for right\n";
		return 1;
	}

	if (number > 255 || number < -255)
	{
		cout << "bite number range is from -255 to 255\n";
		return 1;
	}

	if (rotationCount > 8 || rotationCount < 0)
	{
		cout << "bit count in bite is is from 0 to 8\n";
		return 1;
	}

	int result = RotateNumber(number, rotationCount, *direction);
	cout << result << '\n';	

	return 0;
}

