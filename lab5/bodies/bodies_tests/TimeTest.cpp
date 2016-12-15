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
		//BOOST_REQUIRE(CheckTime(CTime(0, 0, 0)++, 0, 0, 0));
		//BOOST_REQUIRE(CheckTime(CTime(23, 11, 20)++, 23, 11, 20));
		//BOOST_REQUIRE(CheckTime(CTime(23, 59, 59)++, 23, 59, 59));
		//BOOST_REQUIRE(CheckTime(CTime(24, 00, 00)++, 24, 0, 0));
	}

	BOOST_AUTO_TEST_CASE(can_use_prefix_decriment)
	{
		BOOST_REQUIRE(CheckTime(--CTime(10, 10, 20), 10, 10, 19));
		BOOST_REQUIRE(CheckTime(--CTime(23, 59, 59), 23, 59, 58));
	}

	BOOST_AUTO_TEST_CASE(can_use_postfix_decriment)
	{
		//BOOST_REQUIRE(CheckTime(CTime(0, 0, 0)--, 0, 0, 0));
		//BOOST_REQUIRE(CheckTime(CTime(23, 11, 20)--, 23, 11, 20));
		//BOOST_REQUIRE(CheckTime(CTime(23, 59, 59)--, 23, 59, 59));
		//BOOST_REQUIRE(CheckTime(CTime(24, 00, 00)--, 24, 0, 0));
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


BOOST_AUTO_TEST_SUITE_END()