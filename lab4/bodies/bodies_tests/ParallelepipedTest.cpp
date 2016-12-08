#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Parallelepiped.h"
#include <math.h>

struct Parallelepiped_
{
	const double expectedWidth = 22.2;
	const double expectedDepth = 21.5;
	const double expectedHeight = 12.9;
	const double expectedDensity = 3.8;
	const double expectedVolume = expectedWidth * expectedHeight * expectedDepth;
	const CParallelepiped parallelepiped;
	Parallelepiped_()
		: parallelepiped(expectedDensity, expectedWidth, expectedHeight, expectedDepth)
	{}
};

BOOST_FIXTURE_TEST_SUITE(parallelepiped, Parallelepiped_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&parallelepiped));
	}


	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), expectedWidth);
	}


	BOOST_AUTO_TEST_CASE(has_a_depth)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), expectedDepth);
	}


	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), expectedHeight);
	}


	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(parallelepiped).GetDensity(), expectedDensity);
	}


	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(parallelepiped).GetVolume(), expectedVolume, 1e-7);
	}


	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(parallelepiped).GetMass(), expectedDensity * expectedVolume, 1e-7);
	}


	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
const auto expectedString = R"(Parallelepiped:
	density = 3.8
	volume = 6157.17
	mass = 23397.246
	width = 22.2
	height = 12.9
	depth = 21.5
)";
		BOOST_CHECK_EQUAL(parallelepiped.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		BOOST_REQUIRE_THROW(CParallelepiped(-7, 51, -1, 0), std::invalid_argument);
	}
BOOST_AUTO_TEST_SUITE_END()