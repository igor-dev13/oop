#include "stdafx.h"
#include "VectorProcessor.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int _tmain()
{
	cout << "Enter the elements with spaces\n";
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));

	ProcessVector(numbers);

	sort(numbers.begin(), numbers.end());

	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	cout << "\nSize of vector: " << numbers.size() << endl;

	return 0;
}

