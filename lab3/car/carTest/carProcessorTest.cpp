#include "stdafx.h"
#include "../car/car.h"
#include "../car/СarProcessor.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

using namespace std;

struct CarProcessorDependencies
{	
	stringstream output;
	stringstream input;

	CCar car;

	CarProcessorDependencies()
		: car(output)
	{
	}
};

struct CarProcessorFixture : CarProcessorDependencies
{
	CarProcessor carProcessor;

	CarProcessorFixture()
		: carProcessor(car, output)
	{
	}

	void CheckCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();

		BOOST_CHECK(input << command);
		string commandLine = command;
		BOOST_CHECK(carProcessor.HandleCommand(commandLine));
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(CarProcessorTest, CarProcessorFixture)

	BOOST_AUTO_TEST_CASE(can_handle_unknown_command)
	{
		CheckCommandHandling("helloCar", "Unknown command\n");
	}

	BOOST_AUTO_TEST_CASE(can_turn_on_engine)
	{
		CheckCommandHandling("EngineOn", "Car engine is switched on\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_errors)
	{
		CheckCommandHandling("SetGear 1", "Gear didn't change. Only neutral gear can be set when engine is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_result_of_changing_car_status)
	{
		CheckCommandHandling("EngineOff", "The engine is already switched off\n");

		car.TurnOnEngine();
		CheckCommandHandling("EngineOn", "Car engine is already switched on\n");

		CheckCommandHandling("SetGear 1", "selected gear 1\n");
		CheckCommandHandling("SetGear 3", "Gear can't be set. Gear is out of speed range\n");

		CheckCommandHandling("SetSpeed 20", "selected speed 20\n");
		CheckCommandHandling("SetGear 2", "selected gear 2\n");
		CheckCommandHandling("SetSpeed 30", "selected speed 30\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_Info_command)
	{
		CheckCommandHandling("Info", "Engine status: switched off\nSpeed: 0\nDirection: stop\nGear: neutral\n"); 
	}

BOOST_AUTO_TEST_SUITE_END()