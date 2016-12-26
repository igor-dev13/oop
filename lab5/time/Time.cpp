#include "stdafx.h"
#include "Time.h"
#include <new>

using namespace std;

CTime::CTime(unsigned hours, unsigned minutes, unsigned seconds)	
{
	if (minutes > 59 || seconds > 59 || hours > 23)
	{
		m_seconds = 0;
		throw std::invalid_argument("Time must be in certain limits!");
	}
	
	m_seconds = hours * SECONDS_IN_HOUR + minutes * SECONDS_IN_MINUTE + seconds;	
}

CTime::CTime(unsigned timeStamp)
{
	if (timeStamp > SECONDS_IN_DAY)
	{
		m_seconds = 0;
		throw std::invalid_argument("Maximum 86400 seconds in a day!");
	}

	m_seconds = timeStamp;
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
	CTime tmpCopy(m_seconds);
	++*this;
	return tmpCopy;
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
	CTime tmpCopy(m_seconds);
	--*this;
	return tmpCopy;
}

CTime CTime::operator + (CTime const & time2)const
{
	unsigned additionValue = m_seconds + time2.m_seconds;
	return CTime(additionValue % SECONDS_IN_DAY);
}

CTime  CTime::operator - (CTime const & time2)const
{
	signed subtractionValue = m_seconds - time2.m_seconds;
	return CTime((subtractionValue < 0) ? SECONDS_IN_DAY - (subtractionValue * -1) : subtractionValue);
}

CTime & CTime::operator += (CTime const & other)
{
	if (std::addressof(other) != this)
	{
		CTime tmpCopy(other);
		unsigned additionValue = m_seconds + tmpCopy.m_seconds;
		if (additionValue > SECONDS_IN_DAY)
		{
			additionValue -= SECONDS_IN_DAY;
		}
		m_seconds = additionValue;		
	}
	return *this;
}

CTime & CTime::operator -= (CTime const & other)
{
	if (addressof(other) != this)
	{
		CTime tmpCopy(other);
		signed subtractionValue = m_seconds - tmpCopy.m_seconds;
		unsigned subtractionResult;

		if (subtractionValue < 0)
		{
			subtractionResult = SECONDS_IN_DAY - (subtractionValue * -1);
		}
		else
		{
			subtractionResult = subtractionValue;
		}

		m_seconds = subtractionResult;
	}

	return *this;
}

CTime const CTime::operator * (unsigned number)const
{
	unsigned multiplicationValue = m_seconds * number;
	return CTime((multiplicationValue > SECONDS_IN_DAY) ? 
		multiplicationValue % SECONDS_IN_DAY : multiplicationValue);
}

CTime const operator * (unsigned number, CTime const & other)
{
	unsigned multiplicationValue = other.m_seconds * number;
	return CTime((multiplicationValue > SECONDS_IN_DAY) ?
		multiplicationValue % SECONDS_IN_DAY : multiplicationValue);
}

CTime const CTime::operator / (unsigned number)const
{
	if (number == 0)
	{
		throw std::invalid_argument("Can't divide by zero!");
	}
	return CTime(m_seconds / number);
}

unsigned CTime::operator / (CTime const & other)const
{	
	if (other.m_seconds == 0)
	{
		throw std::invalid_argument("Can't divide by zero!");
	}	

	return m_seconds / other.m_seconds;
}

CTime & CTime::operator *= (unsigned number)
{
	m_seconds *= number;

	if (m_seconds > SECONDS_IN_DAY)
	{
		m_seconds = m_seconds % SECONDS_IN_DAY;
	}	
	return *this;
}

unsigned CTime::operator /= (CTime const & other)
{
	CTime tmpCopy(other);

	if (tmpCopy.m_seconds == 0)
	{
		throw std::invalid_argument("Can't divide by zero!");
	}
	return (m_seconds / tmpCopy.m_seconds);	
}

bool CTime::operator == (CTime const & other)const
{
	return (m_seconds == other.m_seconds);
}

bool CTime::operator != (CTime const & other)const
{
	return !(m_seconds == other.m_seconds);
}

bool CTime::operator > (CTime const & other)const
{
	return (m_seconds > other.m_seconds);
}

bool CTime::operator < (CTime const & other)const
{
	return (m_seconds < other.m_seconds);
}

bool CTime::operator >= (CTime const & other)const
{
	return (m_seconds >= other.m_seconds);
}

bool CTime::operator <= (CTime const & other)const
{
	return (m_seconds <= other.m_seconds);
}

string CTime::TimeToString()const
{
    string hours = "0" + to_string(m_seconds / SECONDS_IN_HOUR);
    string minutes = "0" + to_string((m_seconds / SECONDS_IN_MINUTE) - ((m_seconds / SECONDS_IN_HOUR) * SECONDS_IN_MINUTE));
    string seconds = "0" + to_string(m_seconds % SECONDS_IN_MINUTE);

    return hours.substr(hours.size() - 2) + ":" + minutes.substr(minutes.size() - 2) + ":" + seconds.substr(seconds.size() - 2);
}

std::ostream & operator << (std::ostream & output, const CTime & time)
{
	output << time.TimeToString();
	return output;
}