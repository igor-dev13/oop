#include "stdafx.h"
#include "Car.h"

using namespace std;

CCar::CCar()
	: m_gearMap({
		{ Gear::REVERSE, bind(&CCar::SetSpeedRange, this, reverseRangeStart, reverseRangeEnd) },
		{ Gear::FIRST, bind(&CCar::SetSpeedRange, this, firstRangeStart, firstRangeEnd) },
		{ Gear::SECOND, bind(&CCar::SetSpeedRange, this, secondRangeStart, secondRangeEnd) },
		{ Gear::THIRD, bind(&CCar::SetSpeedRange, this, thirdRangeStart, thirdRangeEnd) },
		{ Gear::FOURTH, bind(&CCar::SetSpeedRange, this, fourthRangeStart, fourthRangeEnd) },
		{ Gear::FIFTH, bind(&CCar::SetSpeedRange, this, fifthRangeStart, fifthRangeEnd) }
	})
{
}

CCar::~CCar() = default;

bool CCar::SetSpeedRange(int gearSpeedRangeFrom, int gearSpeedRangeTo)
{
	m_gearRange.clear();
	std::vector<int>::iterator it;

	for (int i = gearSpeedRangeFrom; i <= gearSpeedRangeTo; i++)
	{
		m_gearRange.push_back(i);
	}

	return true;
}

bool CCar::CheckSpeedRange(Gear gear)
{
	auto it = m_gearMap.find(gear);
	if (it != m_gearMap.end())
	{
		it->second(m_speed, m_speed);
		return true;
	}

	return false;
}

bool CCar::TurnOnEngine()
{
	if (!GetEngineStatus())
	{
		m_isEngineOn = true;
		return true;
	}

	return false;		
}

bool CCar::TurnOffEngine()
{
	if (GetEngineStatus() && m_gear == Gear::NEUTRAL && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}

	return false;	
}

bool CCar::SetGear(Gear selectedGear)
{	
	if (selectedGear == Gear::REVERSE && (GetDirection() == Direction::FORWARD))
	{
		return false;
	}

	if (((selectedGear == Gear::FIRST) || (selectedGear == Gear::SECOND)) && (GetDirection() == Direction::BACK))
	{
		return false;
	}

	if (selectedGear != Gear::NEUTRAL)
	{
		bool processNewGear = CheckSpeedRange(selectedGear);

		if (!processNewGear)
			return false;
	}	

	bool gearInSpeedRange = std::find(std::begin(m_gearRange), std::end(m_gearRange), m_speed) != std::end(m_gearRange);

	if (selectedGear == Gear::NEUTRAL || gearInSpeedRange)
	{
		m_gear = selectedGear;
		return true;
	}
	
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (m_gear != Gear::NEUTRAL)
	{
		bool processCurrentGearRange = CheckSpeedRange(GetGear());
		
		if (!processCurrentGearRange)
			return false;
	}		
	
	bool speedInGearRange = std::find(std::begin(m_gearRange), std::end(m_gearRange), speed) != std::end(m_gearRange);

	if (speedInGearRange || (m_gear == Gear::NEUTRAL && speed == 0))
	{
		m_speed = speed;
		return true;
	}

	return false;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::GetEngineStatus() const
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
	else
	{
		return Direction::FORWARD;
	}
}

bool CCar::operator==(const CCar & car)
{
	return (m_isEngineOn == car.m_isEngineOn) && (m_speed == car.m_speed) && (m_gear == car.m_gear);
}