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
	std::string TimeToString()const;
public:
	CTime & operator++();
	CTime const operator++(int);
	CTime & operator--();
	CTime const operator--(int);
	CTime operator + (CTime const & time2)const;
	CTime operator - (CTime const & time2)const;
	CTime & operator += (CTime const & other);
	CTime & operator -= (CTime const & other);
	CTime const operator * (unsigned number)const;
	CTime const friend operator * (unsigned number, CTime const & other);
	CTime const operator / (unsigned number)const;
	unsigned operator / (CTime const & other)const;
	CTime & operator *= (unsigned number);
	unsigned operator /= (CTime const & other);
	bool operator == (CTime const & other)const;
	bool operator != (CTime const & other)const;
	bool operator > (CTime const & other)const;
	bool operator < (CTime const & other)const;
	bool operator >= (CTime const & other)const;
	bool operator <= (CTime const & other)const;
	std::ostream friend & operator << (std::ostream & output, const CTime & time);
private:
	unsigned m_seconds;
};
