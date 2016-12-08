#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Sphere.h"
#include <math.h>


struct Sphere_
{
	const double expectedRadius = 22.6;
	const double expectedDensity = 8.6;
	const double expectedVolume = (pow(expectedRadius, 3) * M_PI) * 4 / 3;
	const CSphere sphere;
	Sphere_()
		: sphere(expectedDensity, expectedRadius)
	{}
};
// Сфера
BOOST_FIXTURE_TEST_SUITE(Sphere, Sphere_)
	// является объемным телом
	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&sphere));
	}
	// имеет радиус
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(sphere.GetRadius(), expectedRadius);
	}
	// имеет плотность
	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(sphere).GetDensity(), expectedDensity);
	}
	// имеет объем
	BOOST_AUTO_TEST_CASE(has_a_volume)
	{		
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sphere).GetVolume(), expectedVolume, 1e-7);
	}
	// имеет массу
	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(sphere).GetMass(), expectedVolume * expectedDensity, 1e-7);
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
	const auto expectedString = R"(Sphere:
	density = 8.6
	volume = 48351.94256
	mass = 415826.706
	radius = 22.6
)";
		BOOST_CHECK_EQUAL(static_cast<const CBody &>(sphere).ToString(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(can_handle_negative_values)
	{
		BOOST_REQUIRE_THROW(CSphere(1, -10), std::invalid_argument);
	}
BOOST_AUTO_TEST_SUITE_END()