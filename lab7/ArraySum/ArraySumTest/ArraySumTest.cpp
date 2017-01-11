#include "stdafx.h"
#include "../ArraySum/ArraySum.h"
#include <vector>
#include <string>

BOOST_AUTO_TEST_SUITE(ArraySum_function)
	BOOST_AUTO_TEST_CASE(can_return_default_constructor_value_if_array_is_empty)
	{
		{
			std::vector<int> testValues = {};
			int sumOfElements = ArraySum(testValues);
			BOOST_CHECK_EQUAL(sumOfElements, 0);
		}
		{
			std::vector<double> testValues = {};
			double sumOfElements = ArraySum(testValues);
			BOOST_CHECK_EQUAL(sumOfElements, 0);
		}
		{
			std::vector<std::string> testValues = {};
			std::string sumOfElements = ArraySum(testValues);
			BOOST_CHECK_EQUAL(sumOfElements, "");
		}
	}
	BOOST_AUTO_TEST_CASE(can_calculate_sum_of_integers)
	{
		std::vector<int> testValues = { 10, -20, 2, 0 };
		int sumOfElements = ArraySum(testValues);
		BOOST_CHECK_EQUAL(sumOfElements, -8);
	}
	BOOST_AUTO_TEST_CASE(can_calculate_sum_of_doubles)
	{
		std::vector<double> testValues = { -10.2, 20.7, 15.9 };
		double sumOfElements = ArraySum(testValues);
		BOOST_CHECK_EQUAL(sumOfElements, 26.4);
	}
	BOOST_AUTO_TEST_CASE(can_calculate_sum_of_strings)
	{
		std::vector<std::string> testValues = { "hello", "My", " ", "best", "friend" };
		std::string sumOfElements = ArraySum(testValues);
		BOOST_CHECK_EQUAL(sumOfElements, "helloMy bestfriend");
	}
BOOST_AUTO_TEST_SUITE_END()