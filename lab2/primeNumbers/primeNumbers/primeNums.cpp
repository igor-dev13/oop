#include "stdafx.h"
#include <vector>
#include <set>

const int MAX_VALUE = 100000000;
const int FIRST_PRIME = 2;

std::vector<bool> InitVectorOfPrimes(unsigned int upperBound)
{
	std::vector<bool> sieve(upperBound + 1, true);
	if (upperBound >= FIRST_PRIME && upperBound < MAX_VALUE + 1)
	{
		sieve[0] = sieve[1] = false;
		for (unsigned int i = FIRST_PRIME; i * i <= upperBound; ++i)
		{
			if (sieve[i])
			{
				for (unsigned int j = i * i; j <= upperBound; j += i)
				{
					sieve[j] = false;
				}
			}
		}
	}
	else
	{
		sieve = {};
	}
	return sieve;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	std::vector<bool> sieve = InitVectorOfPrimes(upperBound);

	std::set<int> result;
	if (upperBound >= FIRST_PRIME && upperBound < MAX_VALUE + 1)
	{
		result.emplace_hint(result.end(), FIRST_PRIME);
		for (unsigned int i = FIRST_PRIME + 1; i <= upperBound; i += 2)
		{
			if (sieve[i])
			{
				result.emplace_hint(result.end(), i);
			}
		}
	}

	return result;
}