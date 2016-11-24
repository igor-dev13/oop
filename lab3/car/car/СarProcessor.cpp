#include "stdafx.h"
#include "ÑarProcessor.h"

using namespace std;
using namespace std::placeholders;

CarProcessor::CarProcessor(CCar & car)
	: m_car(car)
{
}

CarProcessor::~CarProcessor() = default;

string DirectionToString(const Direction & direction)
{
	switch (direction)
	{
	case Direction::BACK:
		return "back";
	case Direction::FORWARD:
		return "forward";
	case Direction::STOP:
		return "stop";
	default:
		return "stop";
	}
}

string GearToString(const Gear & gear)
{
	switch (gear)
	{
	case Gear::REVERSE:
		return "reverse";
	case Gear::NEUTRAL:
		return "neutral";
	case Gear::FIRST:
		return "first";
	case Gear::SECOND:
		return "second";
	case Gear::THIRD:
		return "third";
	case Gear::FOURTH:
		return "fourth";
	case Gear::FIFTH:
		return "fifth";
	default:
		return "neutral";
	}
}

bool IsNumber(const string & str)
{
	try
	{
		return all_of(str.begin(), str.end(), isdigit);
	}
	catch (exception & exception)
	{
		cout << "second argument is not a number" << endl;
		cout << exception.what() << endl;
		return false;
	}	
}

bool CarProcessor::HandleCommand(string & command)
{
	boost::to_lower(command);
	vector<string> commands;
	boost::split(commands, command, boost::is_any_of(" "));
	if (commands.size() == 1 || commands.size() == 2)
	{
		if (commands[0] == "engineon")
		{
			TurnOnEngine();
		}
		else if (commands[0] == "engineoff")
		{
			TurnOffEngine();
		}
		else if ((commands[0] == "info") && (commands.size() == 1))
		{
			GetInfo(m_car);
		}
		else if ((commands[0] == "setgear") && (stoi(commands[1]) >= -1 && stoi(commands[1]) <= 5))
		{
			SetGear(stoi(commands[1]));
		}
		else if ((commands[0] == "setspeed") && (stoi(commands[1]) >= 0))
		{
			SetSpeed(stoi(commands[1]));
		}
		else
		{
			cout << "Unknown command" << endl;
		}	
	}
	else
	{
		cout << "Unknown command" << endl;
	}

	return true;
}

Gear CarProcessor::IntToGear(const int gear)
{
	if (gear >= -1 && gear <= 5)
	{
		switch (gear)
		{
		case -1:
			return Gear::REVERSE;
		case 0:
			return Gear::NEUTRAL;
		case 1:
			return Gear::FIRST;
		case 2:
			return Gear::SECOND;
		case 3:
			return Gear::THIRD;
		case 4:
			return Gear::FOURTH;
		case 5:
			return Gear::FIFTH;
		default:
			return Gear::NEUTRAL;
		}
	}
	throw runtime_error("gear must be -1..5");
}

bool CarProcessor::TurnOnEngine()
{
	bool result = m_car.TurnOnEngine();

	if (result)
	{
		cout << "Car engine is switched on" << endl;
	}
	else 
	{
		cout << "Car engine is already switched on" << endl;
	}
	
	return result;
}

bool CarProcessor::TurnOffEngine()
{
	bool result = m_car.TurnOffEngine();

	if (result)
	{
		cout << "Car engine is switched off" << endl;
	}
	else
	{
		cout << "It is impossible to turn off the engine" << endl;
	}

	return result;
}

bool CarProcessor::SetGear(int gear)
{
	if (!m_car.GetEngineStatus())
	{
		cout << "Car engine is turned off" << endl;
		return false;
	}

	try
	{
		Gear carGear = IntToGear(gear);
		bool result = m_car.SetGear(carGear);
		if (result)
		{
			cout << "selected gear " << gear << endl;
		}
		else
		{
			cout << "gear didn't change" << endl;
		}
		return result;
	}
	catch (exception & exception)
	{
		cout << "gear didn't change" << endl;
		cout << exception.what() << endl;
		return false;
	}
}

bool CarProcessor::SetSpeed(int speed)
{
	if (!m_car.GetEngineStatus())
	{
		cout << "engine is turn off" << endl;
		return false;
	}

	bool result = m_car.SetSpeed(speed);
	if (result)
	{
		cout << "selected speed " << speed << endl;
	}
	else
	{
		cout << "speed didn't changed" << endl;
	}

	return result;	
}

void CarProcessor::GetInfo(const CCar & car)
{
	cout << "Engine status: " << ((car.GetEngineStatus()) ? ("turned on") : ("turned off")) << endl;
	cout << "Speed: " << car.GetSpeed() << endl;
	cout << "Direction: " << DirectionToString(car.GetDirection()).c_str() << endl;
	cout << "Gear: " << GearToString(car.GetGear()).c_str() << endl;
}