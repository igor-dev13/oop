#pragma once

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH };
enum class Direction { BACK, STOP, FORWARD };

class CCar
{
public:
	std::ostream & m_output;
public:
	CCar(std::ostream &output);
	~CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool IsEngineOn() const;	
	bool SetGear(Gear selectedGear);
	bool SetSpeed(int speed);
	int GetSpeed() const;
	Gear GetGear() const;
	Direction GetDirection() const;	
private:
	bool m_isEngineOn = false;
	Gear m_gear = Gear::NEUTRAL;
	Gear previousGear;
	int m_speed = 0;
};