#include "stdafx.h"
#include "../Body.h"
#include "../Sphere.h"
#include "../Controller.h"
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// зависимости controller'a
struct ControllerDependencies
{
	vector<shared_ptr<CBody>> bodies;
	stringstream input;
	stringstream output;
};

struct ControllerFixture : ControllerDependencies
{
	CController controller;

	ControllerFixture() : controller(bodies, input, output)
	{
	}

	void CheckCommandHandling(const string &command, const string &expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		controller.HandleCommand();
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void ExpectSuccess(const std::vector<std::shared_ptr<CBody>> &bodies, const size_t expectedVectorSize,
		const double expectedDensity, const double expectedMass, const double expectedVolume)
	{
		BOOST_CHECK_EQUAL(bodies.size(), expectedVectorSize);
		BOOST_CHECK_EQUAL(bodies.back()->GetDensity(), expectedDensity);
		BOOST_CHECK_EQUAL(bodies.back()->GetMass(), expectedMass);
		BOOST_CHECK_EQUAL(bodies.back()->GetVolume(), expectedVolume);
	}
};

BOOST_FIXTURE_TEST_SUITE(Controller, ControllerFixture)

	BOOST_AUTO_TEST_SUITE(when_handling_commands_by_user)
		BOOST_AUTO_TEST_CASE(cannot_create_bodies_with_negative_parametrs)
		{
			CheckCommandHandling("CreateSphere 4 -2", "Density and radius should not be negative.\n");
			CheckCommandHandling("CreateParallelepiped 3 3 -2 2", "Density, width, height and depth can't be negative.\n");
			CheckCommandHandling("CreateCone -7 2 3", "Density, base radius and height can't be negative.\n");
			CheckCommandHandling("CreateCylinder 4 4 -1", "Density, base radius and height can't be negative.\n");
			BOOST_CHECK_EQUAL(bodies.size(), 0);
		}
		BOOST_AUTO_TEST_CASE(can_create_any_available_geometric_body)
		{
			CheckCommandHandling("CreateCone 60 6 3", "Cone created.\n");
			ExpectSuccess(bodies, 1, 60, M_PI * 6 * 6 * 3 / 3 * 60, M_PI * 6 * 6 * 3 / 3);
			CheckCommandHandling("CreateSphere 14 5", "Sphere created.\n");
			ExpectSuccess(bodies, 2, 14, (pow(5, 3) * M_PI) * 4 / 3 * 14, (pow(5, 3) * M_PI) * 4 / 3);
			CheckCommandHandling("CreateCylinder 54 6 2", "Cylinder created.\n");
			ExpectSuccess(bodies, 3, 54, M_PI * pow(6, 2) * 2 * 54, M_PI * pow(6, 2) * 2);
			CheckCommandHandling("CreateParallelepiped 12 15 10 10", "Parallelepiped created.\n");
			ExpectSuccess(bodies, 4, 12, 10 * 12 * 15 * 10, 15 * 10 * 10);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(check_GetBodyWeightInWater_method)
		BOOST_AUTO_TEST_CASE(can_return_negative_value)
		{
			CSphere sphere(300, 10);
			BOOST_CHECK(controller.GetBodyWeightInWater(sphere) < 0);
		}

		BOOST_AUTO_TEST_CASE(can_return_positive_value)
		{
			CSphere sphere(1200, 12);
			BOOST_CHECK(controller.GetBodyWeightInWater(sphere) > 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()