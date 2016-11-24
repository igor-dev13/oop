#include "stdafx.h"
#include "../car/car.h"
#include "../car/ÑarProcessor.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

using namespace std;
using namespace std::placeholders;

struct  CarProcessorDependencies
{
	CCar car;	
};

struct CarProcessorFixture : CarProcessorDependencies
{
	CarProcessor carProcessor;	

	CarProcessorFixture()
		: carProcessor(car)
	{
	}	

	void CheckCommandHandling(const string& command, const string& expectedOutput)
	{
		stringstream input;
		stringstream output;

		output = stringstream();
		input = stringstream();
		
		BOOST_CHECK(input << command);
		string commandLine = command;
		BOOST_CHECK(carProcessor.HandleCommand(commandLine));

		//BOOST_CHECK(input.eof());
		//BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};



BOOST_FIXTURE_TEST_SUITE(CarProcessorTest, CarProcessorFixture)

	BOOST_AUTO_TEST_CASE(can_turn_on_engine)
	{
		CheckCommandHandling("EngineOn", "Car engine is switched on\n");
	}

BOOST_AUTO_TEST_SUITE_END()