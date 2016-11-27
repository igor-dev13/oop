#pragma once
#include "car.h"

class CarProcessor
{
public:
	std::ostream & m_output;
public:	
	CarProcessor(CCar & car, std::ostream &output);
	~CarProcessor();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);	
	bool HandleCommand(std::string & command);
	Gear IntToGear(const int gear);
	void GetInfo(const CCar & car);
private:
	CCar & m_car;	
};