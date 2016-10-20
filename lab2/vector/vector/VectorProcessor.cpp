#include "stdafx.h"
#include "VectorProcessor.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

using namespace std;
using namespace std::placeholders;
using namespace boost::phoenix::placeholders;
using namespace boost::phoenix;
using boost::transform;

void ProcessVector(vector<double> & numbers)
{
	if (!numbers.empty())
	{
		double minElem = *min_element(numbers.begin(), numbers.end());

		for (size_t i = 0; i < numbers.size(); ++i)
		{
			numbers[i] *= minElem;
		}		
	}
}

void SortVector(vector<double> & numbers)
{
	sort(numbers.begin(), numbers.end());
}

