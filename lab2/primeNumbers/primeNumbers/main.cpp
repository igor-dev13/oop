#include "stdafx.h"
#include <iostream>
#include <set>
#include "primeNumbers.h"

const int MAX_NUM_OF_ARG = 2;
const int MAX_VALUE = 100000000;

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != MAX_NUM_OF_ARG)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: primeNumbers.exe <upperBound>" << endl;
		return EXIT_FAILURE;
	}

	int upperBound = atoi(argv[1]);
	if ((upperBound <= 0) || (upperBound > MAX_VALUE))
	{
		cout << "Invalid argument" << endl
			<< "Upper bound in [1, 100000000]" << endl;
		return EXIT_FAILURE;
	}

	set<int> prime = GeneratePrimeNumbersSet(upperBound);

	cout << prime.size() << endl;
	return EXIT_SUCCESS;
}