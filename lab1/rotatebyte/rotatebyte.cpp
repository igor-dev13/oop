#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

enum class RotationDirection
{
	NONE,
	LEFT,
	RIGHT 
};

RotationDirection GetRotateDirection(const string &choice)
{
	if (choice == "R")
	{
		return RotationDirection::RIGHT;
	}
	else if (choice == "L")
	{
		return RotationDirection::LEFT;
	}
	else
	{
		return RotationDirection::NONE;
	}
}

uint8_t RotateByte(uint8_t byte, unsigned bits, const RotationDirection direction)
{
	bits %= 8;

	switch (direction)
	{
		case RotationDirection::RIGHT:
		{
			byte = (byte >> bits) | (byte << (8 - bits));
			break;
		}
		case RotationDirection::LEFT:
		{
			byte = (byte << bits) | (byte >> (8 - bits));
			break;
		}
	}

	return byte;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return 1;
	}

	unsigned byte, bits;

	try
	{
		byte = stoi(argv[1]);
	}
	catch (const invalid_argument)
	{
		cout << "Enter a valid integer number for <bite>" << endl;
		return 1;
	}	

	try
	{
		bits = stoi(argv[2]);
	}
	catch (const invalid_argument)
	{
		cout << "Enter a valid integer number for  <number of bits>" << endl;
		return 1;
	}

	if ((byte < 0) || (byte > 255))
	{
		cout << "bite number range is from 0 to 255" << endl;
		return 1;
	}	

	string rotationWay = argv[3];
	RotationDirection direction = GetRotateDirection(rotationWay);
	
	if (direction != RotationDirection::RIGHT && direction != RotationDirection::LEFT)
	{
		cout << "Enter a valid direction, uppercase - L for left, or R for right" << endl;
		return 1;
	}	

	byte = RotateByte(byte, bits, direction);
	cout << byte << endl;

	return 0;
}