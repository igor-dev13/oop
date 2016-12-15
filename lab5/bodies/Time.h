#pragma once

#define SECONDS_IN_DAY 86400 
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60

class CTime
{
public:
	CTime(unsigned hours, unsigned minutes, unsigned seconds = 0);
	CTime(unsigned timeStamp = 0);
	unsigned GetHours()const;
	unsigned GetMinutes()const;
	unsigned GetSeconds()const;
	bool IsValid()const;
public:
	CTime & operator++();
	CTime const operator++(int);
	CTime & operator--();
	CTime const operator--(int);
	CTime operator + (CTime const & time2);
	CTime operator - (CTime const & time2);
	CTime & operator = (CTime const & other);
private:
	unsigned m_seconds;
	bool m_valid;
};
