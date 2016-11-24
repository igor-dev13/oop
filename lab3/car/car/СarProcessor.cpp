#include "stdafx.h"
#include "ÑarProcessor.h"

using namespace std;
using namespace std::placeholders;

CarProcessor::CarProcessor(CCar & car, std::ostream &output)
	: m_car(car)
	, m_output(output)
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
			m_output << "Unknown command" << endl;
		}	
	}
	else
	{
		m_output << "Unknown command" << endl;
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
		m_output << "Car engine is switched on" << endl;
	}
	else 
	{
		m_output << "Car engine is already switched on" << endl;
	}
	
	return result;
}

bool CarProcessor::TurnOffEngine()
{
	bool result = m_car.TurnOffEngine();

	if (result)
	{
		m_output << "Car engine is switched off" << endl;
	}
	else
	{
		m_output << "The engine is already switched off" << endl;
	}

	return result;
}

bool CarProcessor::SetGear(int gear)
{
	if (!m_car.GetEngineStatus())
	{
		m_output << "Car engine is turned off" << endl;
		return false;
	}

	try
	{
		Gear carGear = IntToGear(gear);
		bool result = m_car.SetGear(carGear);
		if (result)
		{
			m_output << "selected gear " << gear << endl;
		}
		else
		{
			m_output << "gear didn't change" << endl;
		}
		return result;
	}
	catch (exception & exception)
	{
		m_output << "gear didn't change" << endl;
		m_output << exception.what() << endl;
		return false;
	}
}

bool CarProcessor::SetSpeed(int speed)
{
	if (!m_car.GetEngineStatus())
	{
		m_output << "engine is turn off" << endl;
		return false;
	}

	bool result = m_car.SetSpeed(speed);
	if (result)
	{
		m_output << "selected speed " << speed << endl;
	}
	else
	{
		m_output << "speed didn't changed" << endl;
	}

	return result;	
}

void CarProcessor::GetInfo(const CCar & car)
{
	m_output << "Engine status: " << ((car.GetEngineStatus()) ? ("turned on") : ("turned off")) << endl;
	m_output << "Speed: " << car.GetSpeed() << endl;
	m_output << "Direction: " << DirectionToString(car.GetDirection()).c_str() << endl;
	m_output << "Gear: " << GearToString(car.GetGear()).c_str() << endl;
}