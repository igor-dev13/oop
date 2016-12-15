#include "stdafx.h"
#include "Time.h"

using namespace std;

CTime::CTime(unsigned hours, unsigned minutes, unsigned seconds)	
{
	if ((minutes > 59 || seconds > 59) || (hours >= 24 && minutes > 0 && seconds > 0))
	{
		m_valid = false;
		m_seconds = 0;
		throw std::invalid_argument("Time must be in certain limits!");
	}

	m_valid = true;
	m_seconds = hours * SECONDS_IN_HOUR + minutes * SECONDS_IN_MINUTE + seconds;
}

CTime::CTime(unsigned timeStamp)
{
	if (timeStamp > SECONDS_IN_DAY)
	{
		m_valid = false;
		m_seconds = 0;
		throw std::invalid_argument("Maximum 86400 seconds in a day!");
	}

	m_valid = true;
	m_seconds = timeStamp;
}

bool CTime::IsValid() const
{
	return m_valid;
}

unsigned CTime::GetHours()const
{
	return m_seconds / SECONDS_IN_HOUR;
}

unsigned CTime::GetMinutes()const
{
	return m_seconds / SECONDS_IN_MINUTE - (m_seconds / SECONDS_IN_HOUR) * SECONDS_IN_MINUTE;
}

unsigned CTime::GetSeconds()const
{
	return m_seconds % SECONDS_IN_MINUTE;
}

// префиксный инкремент
CTime & CTime::operator++()
{
	++m_seconds;
	if (m_seconds >= SECONDS_IN_DAY)
	{
		m_seconds = m_seconds - SECONDS_IN_DAY;
	}
	return *this;
}

// постфиксный инкремент
CTime const CTime::operator++(int)
{
	//std::shared_ptr<CTime> localTime = *this;
	++m_seconds;
	if (m_seconds >= SECONDS_IN_DAY)
	{
		m_seconds = m_seconds - SECONDS_IN_DAY;
	}
	return *this;
}

CTime & CTime::operator--()
{
	if (m_seconds == 0)
	{
		m_seconds = SECONDS_IN_DAY - 1;
	}
	else 
	{
		m_seconds = m_seconds - 1;
	}
	return *this;
}

CTime const CTime::operator--(int)
{
	return --*this;
}

CTime CTime::operator + (CTime const & time2)
{
	unsigned additionValue = m_seconds + time2.m_seconds;
	return CTime(additionValue % SECONDS_IN_DAY);
}

CTime  CTime::operator - (CTime const & time2)
{
	signed subtractionValue = m_seconds - time2.m_seconds;
	return CTime((subtractionValue < 0) ? SECONDS_IN_DAY - (subtractionValue * -1) : subtractionValue);
}

CTime & CTime::operator = (CTime const & other)
{
	if (std::addressof(other) != this)
	{
		CTime tmpCopy(other);
		m_seconds = tmpCopy.m_seconds;
	}
	return *this;
}