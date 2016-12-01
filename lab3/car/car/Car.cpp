#include "stdafx.h"
#include "Car.h"

using namespace std;

static const vector<pair<int, int>> gearMap = {
	{ -20, 0 },
	{ 0, 30 },
	{ 20, 50 },
	{ 30, 60 },
	{ 40, 90 },
	{ 50, 150 }
};

CCar::CCar(std::ostream &output)
	: m_output(output)
{
}

CCar::~CCar() = default;

bool CCar::TurnOnEngine()
{
	if (!IsEngineOn())
	{
		m_isEngineOn = true;
		m_output << "Car engine is switched on" << endl;
		return true;
	}

	m_output << "Car engine is already switched on" << endl;
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_speed > 0)
	{
		m_output << "The engine is already switched off" << endl;
		return false;
	}

	if (IsEngineOn() && m_gear == Gear::NEUTRAL && m_speed == 0)
	{
		m_isEngineOn = false;
		m_output << "Car engine is switched off" << endl;
		return true;
	}

	m_output << "The engine is already switched off" << endl;
	return false;
}

bool CCar::SetGear(Gear selectedGear)
{
	if (IsEngineOn())
	{
		if (selectedGear == Gear::REVERSE)
		{
			if (m_gear == Gear::REVERSE || ((m_gear == Gear::FIRST || m_gear == Gear::NEUTRAL) && (m_speed == 0)))
			{
				m_gear = selectedGear;
				return true;
			}

			m_output << "Gear can't be set to reverse, car is in other direction" << endl;
			return false;
		}

		if (selectedGear == Gear::NEUTRAL)
		{
			previousGear = m_gear;
			m_gear = selectedGear;
			return true;
		}

		if (selectedGear > Gear::NEUTRAL && selectedGear <= Gear::FIFTH)
		{
			if (m_speed < 0)
			{
				m_output << "Gear can't be set, car is moving back" << endl;
				return false;
			}

			if (m_speed >= gearMap[static_cast<int>(selectedGear)].first && m_speed <= gearMap[static_cast<int>(selectedGear)].second)
			{
				m_gear = selectedGear;
				return true;
			}

			m_output << "Gear can't be set. Gear is out of speed range" << endl;
			return false;
		}

	}
	else if (!IsEngineOn() && selectedGear == Gear::NEUTRAL)
	{
		m_gear = selectedGear;
		return true;
	}
	else 
	{
		m_output << "Gear didn't change. Only neutral gear can be set when engine is turned off" << endl;
		return false;
	}
}

bool CCar::SetSpeed(int speed)
{
	Gear sign;
	if (IsEngineOn())
	{
		if (m_gear == Gear::NEUTRAL)
		{
			if ((speed > m_speed && m_speed > 0) || ((m_speed >= -20) && speed < 0))
			{
				m_output << "Speed can't be set. Can't increase speed in neutral gear" << endl;
				return false;
			}			
		}

		speed = m_gear == Gear::REVERSE ? -speed : speed;
		sign = m_gear == Gear::REVERSE ? Gear::NEUTRAL : m_gear;

		if (speed >= gearMap[static_cast<int>(sign)].first && speed <= gearMap[static_cast<int>(sign)].second)
		{
			m_speed = speed;
			return true;
		}
		else 
		{
			m_output << "Speed can't be set. Speed is out of gear range" << endl;
			return false;
		}
	}
	else
	{
		m_output << "Speed can't be set when engine is turned off" << endl;
		return false;
	}

	m_output << "Speed didn't change" << endl;
	return false;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	if (m_speed < 0)
	{
		return -m_speed;
	}

	return m_speed;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

Direction CCar::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::STOP;
	}
	else if (m_gear == Gear::REVERSE)
	{
		return Direction::BACK;
	}
	else if (m_gear == Gear::NEUTRAL && previousGear != Gear::NEUTRAL)
	{
		if (previousGear == Gear::REVERSE)
		{
			return Direction::BACK;
		}
		
		return Direction::FORWARD;
	}
	else
	{
		return Direction::FORWARD;
	}
}