#include "stdafx.h"
#include "..\vector\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Function ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// если в векторе есть элемент - 0, то все остальные элементы будут нулями
	BOOST_AUTO_TEST_CASE(mult_all_elements_at_zero)
	{
		vector<double> numbers = { 1, 4, 9, 3, 0 };
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { 0, 0, 0, 0, 0 }));
	}

	BOOST_AUTO_TEST_CASE(makes_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	// при обработке вектора 
	BOOST_AUTO_TEST_SUITE(vector_with_elements)
	// умножение каждого элемента в векторе на минимальный элемент
	BOOST_AUTO_TEST_CASE(mult_all_elements_at_negative_value)
	{
		vector<double> numbers = { -9, 1, 7, 13 };
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { 81, -9, -63, -117 }));		
	}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()