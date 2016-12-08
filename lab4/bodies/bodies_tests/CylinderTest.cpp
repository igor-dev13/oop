#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Cylinder.h"
#include <math.h>

struct Cylinder_
{
	const double expectedRadius = 8.1;
	const double expectedHeight = 5.3;
	const double expectedDensity = 91.2;
	const double expectedVolume = M_PI * expectedRadius * expectedRadius * expectedHeight;
	const CCylinder cylinder;
	Cylinder_()
		: cylinder(expectedDensity, expectedRadius, expectedHeight)
	{}
};

// Цилиндр
BOOST_FIXTURE_TEST_SUITE(Cylinder, Cylinder_)

	// является объемным телом
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cylinder));
	}

	// имеет радиус
	BOOST_AUTO_TEST_CASE(has_a_base_radius)
	{
		BOOST_CHECK_EQUAL(cylinder.GetBaseRadius(), expectedRadius);
	}

	// имеет высоту
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cylinder.GetHeight(), expectedHeight);
	}

	// имеет плотность
	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).GetDensity(), expectedDensity);
	}

	// имеет объем
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetVolume(), expectedVolume, 1e-7);
	}

	// имеет массу
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}

	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
const auto expectedString = R"(Cylinder:
	density = 91.2
	volume = 1092.435438
	mass = 99630.11196
	base radius = 8.1
	height = 5.3
)";
		BOOST_CHECK_EQUAL(cylinder.ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		BOOST_REQUIRE_THROW(CCylinder(-9, 5, 3), std::invalid_argument);
	}
BOOST_AUTO_TEST_SUITE_END()