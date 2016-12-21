#include "stdafx.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TimeTest

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <boost/optional.hpp>

#include "../Time.h"

using namespace std;

struct TimeFixture
{
	CTime time;
};

bool CheckTime(const CTime & time, unsigned hours, unsigned minutes, unsigned seconds)
{
	return ((time.GetHours() == hours) && (time.GetMinutes() == minutes) && (time.GetSeconds() == seconds));
}

BOOST_FIXTURE_TEST_SUITE(Date, TimeFixture)
BOOST_AUTO_TEST_CASE(can_initialize_time)
{
	CTime time1(0, 0, 0);
	BOOST_CHECK(time1.IsValid() == true);

	CTime time2(5, 21, 10);
	BOOST_CHECK(time2.IsValid() == true);

	CTime time3(190);
	BOOST_CHECK(time3.IsValid() == true);
}

BOOST_AUTO_TEST_CASE(can_handle_wrong_values)
{
	BOOST_REQUIRE_THROW(CTime time1(99, 1, 7), std::invalid_argument);

	BOOST_REQUIRE_THROW(CTime time2(86401), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(can_return_only_hours)
{
	CTime time1(17, 21, 20);
	BOOST_CHECK_EQUAL(time1.GetHours(), 17);

	CTime time2(20460);
	BOOST_CHECK_EQUAL(time2.GetHours(), 5);
}

BOOST_AUTO_TEST_CASE(can_return_only_minutes)
{
	CTime time1(17, 21, 20);
	BOOST_CHECK_EQUAL(time1.GetMinutes(), 21);

	CTime time2(20460);
	BOOST_CHECK_EQUAL(time2.GetMinutes(), 41);
}

BOOST_AUTO_TEST_CASE(can_return_only_seconds)
{
	CTime time1(17, 21, 20);
	BOOST_CHECK_EQUAL(time1.GetSeconds(), 20);

	CTime time2(20460);
	BOOST_CHECK_EQUAL(time2.GetSeconds(), 0);
}

BOOST_AUTO_TEST_CASE(can_return_hours_minutes_and_seconds)
{
	CTime time1(17, 21, 20);
	BOOST_REQUIRE(CheckTime(time1, 17, 21, 20));

	CTime time2(20460);
	BOOST_REQUIRE(CheckTime(time2, 5, 41, 0));
}

BOOST_AUTO_TEST_CASE(can_handle_the_limit_values)
{
	CTime time1(86400);
	BOOST_REQUIRE(CheckTime(time1, 24, 0, 0));
}

BOOST_AUTO_TEST_CASE(can_use_prefix_increment)
{
	BOOST_REQUIRE(CheckTime(++CTime(10, 10, 20), 10, 10, 21));
	BOOST_REQUIRE(CheckTime(++CTime(23, 59, 59), 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(can_use_postfix_increment)
{
	CTime time1(0, 0, 0);
	BOOST_REQUIRE(CheckTime(time1++, 0, 0, 0));
	BOOST_REQUIRE(CheckTime(time1, 0, 0, 1));

	CTime time2(23, 59, 59);
	BOOST_REQUIRE(CheckTime(time2++, 23, 59, 59));
	BOOST_REQUIRE(CheckTime(time2, 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(can_use_prefix_decriment)
{
	BOOST_REQUIRE(CheckTime(--CTime(10, 10, 20), 10, 10, 19));
	BOOST_REQUIRE(CheckTime(--CTime(23, 59, 59), 23, 59, 58));
}

BOOST_AUTO_TEST_CASE(can_use_postfix_decriment)
{
	CTime time1(0, 0, 0);
	BOOST_REQUIRE(CheckTime(time1--, 0, 0, 0));
	BOOST_REQUIRE(CheckTime(time1, 23, 59, 59));

	CTime time2(23, 59, 59);
	BOOST_REQUIRE(CheckTime(time2--, 23, 59, 59));
	BOOST_REQUIRE(CheckTime(time2, 23, 59, 58));
}

BOOST_AUTO_TEST_CASE(can_handle_addition_operator_wrong_result)
{
	BOOST_REQUIRE(!CheckTime(CTime(0, 0, 0) + CTime(23, 01, 01), 0, 0, 0));
	BOOST_REQUIRE(!CheckTime(CTime(0, 0, 0) + CTime(20, 22, 24), 11, 11, 10));
}

BOOST_AUTO_TEST_CASE(can_use_addition_operator)
{
	BOOST_REQUIRE(CheckTime(CTime(9, 15, 21) + CTime(3, 8, 17), 12, 23, 38));
	BOOST_REQUIRE(CheckTime(CTime(22, 50, 00) + CTime(2, 15, 00), 1, 05, 0));
	BOOST_REQUIRE(CheckTime(CTime(23, 59, 59) + CTime(0, 0, 5), 0, 0, 4));
}

BOOST_AUTO_TEST_CASE(can_handle_substraction_operator_wrong_result)
{
	BOOST_REQUIRE(!CheckTime(CTime(0, 0, 1) - CTime(6, 20, 30), 0, 0, 0));

}

BOOST_AUTO_TEST_CASE(can_use_substraction_operator)
{
	BOOST_REQUIRE(CheckTime(CTime(20, 0, 0) - CTime(5, 10, 20), 14, 49, 40));
	BOOST_REQUIRE(CheckTime(CTime(0, 0, 2) - CTime(0, 0, 10), 23, 59, 52));
}

BOOST_AUTO_TEST_CASE(can_use_assignment_operator)
{
	CTime time1(10);
	CTime time2(20);
	time1 = time2;

	BOOST_REQUIRE(CheckTime(time1, 0, 0, 20));
}

BOOST_AUTO_TEST_CASE(can_handle_assignment_addition_operator_wrong_result)
{
	CTime time1(100);
	CTime time2(150);
	time2 += time1;

	BOOST_REQUIRE(!CheckTime(time2, 0, 0, 10));
}

BOOST_AUTO_TEST_CASE(can_use_assignment_addition_operator)
{
	CTime time1(40);
	CTime time2(65);
	time2 += time1;

	BOOST_REQUIRE(CheckTime(time2, 0, 1, 45));
}

BOOST_AUTO_TEST_CASE(can_handle_assignment_subtraction_operator_wrong_result)
{
	CTime time1(150);
	CTime time2(50);
	time1 -= time2;

	BOOST_REQUIRE(!CheckTime(time2, 0, 0, 20));
}

BOOST_AUTO_TEST_CASE(can_use_assignment_subtraction_operator)
{
	CTime time1(185);
	CTime time2(50);
	time1 -= time2;

	BOOST_REQUIRE(CheckTime(time1, 0, 2, 15));
}

BOOST_AUTO_TEST_CASE(can_handle_multiplocation_operator_wrong_result)
{
	CTime time1(2);
	CTime time2(2);
	time1 *= time2;

	BOOST_REQUIRE(!CheckTime(time1, 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(can_use_assignment_multiplocation_operator)
{
	CTime time1(10);
	CTime time2(10);
	time1 *= time2;

	BOOST_REQUIRE(CheckTime(time1, 0, 1, 40));
}

BOOST_AUTO_TEST_CASE(can_handle_assignment_division_by_zero)
{
	CTime time1(10);
	CTime time2(0);
	BOOST_REQUIRE_THROW(time1 /= time2, std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(can_use_assignment_division_operator)
{
	CTime time3(10);
	CTime time4(1);
	time3 /= time4;

	BOOST_REQUIRE(CheckTime(time3, 0, 0, 10));

	CTime time5(1);
	CTime time6(10);
	time5 /= time6;

	BOOST_REQUIRE(CheckTime(time5, 0, 0, 1));
}

BOOST_AUTO_TEST_CASE(can_handle_multiplication_operator_wrong_result)
{
	CTime multiplicationValue = CTime(0, 10, 0) * 3;
	BOOST_CHECK(!CheckTime(multiplicationValue, 0, 10, 0));
}

BOOST_AUTO_TEST_CASE(can_use_multiplication_operator)
{
	CTime multiplicationValue1 = CTime(3, 5, 15) * 3;
	BOOST_CHECK(CheckTime(multiplicationValue1, 9, 15, 45));

	CTime multiplicationValue2 = CTime(3, 5, 15) * 0;
	BOOST_CHECK(CheckTime(multiplicationValue2, 0, 0, 0));

	CTime multiplicationValue3 = 3 * CTime(0, 10, 0);
	BOOST_CHECK(CheckTime(multiplicationValue3, 0, 30, 0));
}

BOOST_AUTO_TEST_CASE(can_handle_division_by_zero)
{
	BOOST_REQUIRE_THROW(CTime(10) / 0, std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(can_handle_division_by_negative_value)
{
	BOOST_REQUIRE_THROW(CTime(10) / CTime(-5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(can_use_division_operator)
{
	BOOST_CHECK(CheckTime(CTime(42) / 10, 0, 0, 4));
	BOOST_CHECK(CheckTime(CTime(40) / 10, 0, 0, 4));
	BOOST_CHECK(CheckTime(CTime(100) / CTime(10), 0, 0, 10));
	BOOST_CHECK(CheckTime(CTime(100) / CTime(1000), 0, 0, 0));
	BOOST_CHECK(CheckTime(CTime(5, 0, 0) / CTime(10, 0, 0), 0, 0, 0));
}

BOOST_AUTO_TEST_CASE(can_use_comparison_operator)
{
	CTime time1(10);
	CTime time2(10);
	CTime time3(20);

	BOOST_CHECK(time1 == time1);
	BOOST_CHECK(time1 == time2);
	BOOST_CHECK(time1 != time3);
}

BOOST_AUTO_TEST_CASE(can_use_strict_comparison_operator)
{
	CTime time1(10);
	CTime time2(20);
	CTime time3(30);

	BOOST_CHECK(time3 > time1);
	BOOST_CHECK(!(time3 < time2));	
	BOOST_CHECK(time1 < time2);
}

BOOST_AUTO_TEST_CASE(can_use_nonstrict_comparison_operator)
{
	CTime time1(40);
	CTime time2(50);
	CTime time3(60);	

	BOOST_REQUIRE(!(time1 >= time2));
	BOOST_REQUIRE(time1 <= time2);
	BOOST_REQUIRE(!(time2 >= time3));
}

BOOST_AUTO_TEST_CASE(can_output_time)
{
	CTime time(75490);
	std::stringstream output;
	output << time;
	BOOST_CHECK_EQUAL(output.str(), "20:58:10");
	output.str(std::string());

	CTime time2(8, 41, 27);
	output << time2;
	BOOST_CHECK_EQUAL(output.str(), "08:41:27");
	output.clear();
}

BOOST_AUTO_TEST_SUITE_END()