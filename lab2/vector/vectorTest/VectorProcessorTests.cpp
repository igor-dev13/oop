#include "stdafx.h"
#include "..\vector\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Function SortVector
BOOST_AUTO_TEST_SUITE(SortVector_function)

	// �������� ������� ���������� ��������� �������
	BOOST_AUTO_TEST_CASE(sort_vector_elements)
	{
		vector<double> numbers = { 3, 1, 4, 2 };
		SortVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { 1, 2, 3, 4 }));
	}

BOOST_AUTO_TEST_SUITE_END()

// Function ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// ���� � ������� ���� ������� - 0, �� ��� ��������� �������� ����� ������
	BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_no_positive_numbers)
	{
		vector<double> numbers = { 1, 4, 9, 3, 0 };
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { 0, 0, 0, 0, 0 }));
	}

	// ��� ��������� ������� 
	BOOST_AUTO_TEST_SUITE(vector_with_elements)
	// ��������� ������� �������� � ������� �� ����������� �������
	BOOST_AUTO_TEST_CASE(adding_the_arithmetic_average_of_each_element)
	{
		vector<double> numbers = { -9, 1, 7, 13 };
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers, { 81, -9, -63, -117 }));		
	}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()