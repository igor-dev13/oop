#pragma once

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH };
enum class Direction { BACK, STOP, FORWARD };

class CCar
{
public:
	const int reverseRangeStart = 0;
	const int reverseRangeEnd = 20;
	const int firstRangeStart = 0;
	const int firstRangeEnd = 30;
	const int secondRangeStart = 20;
	const int secondRangeEnd = 50;
	const int thirdRangeStart = 30;
	const int thirdRangeEnd = 60;
	const int fourthRangeStart = 40;
	const int fourthRangeEnd = 90;
	const int fifthRangeStart = 50;
	const int fifthRangeEnd = 150;
public:
	CCar();
	~CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear selectedGear);
	bool SetSpeed(int speed);
	bool SetSpeedRange(int gearSpeedRangeFrom, int gearSpeedRangeTo);
	bool CheckSpeedRange(Gear gear);
	bool GetEngineStatus() const;
	int GetSpeed() const;
	Gear GetGear() const;
	Direction GetDirection() const;	
	bool operator==(const CCar & car);
private:
	bool m_isEngineOn = false;
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
	typedef std::map<Gear, std::function<bool(int gearSpeedRangeFrom, int gearSpeedRangeTo)>> GearMap;
	const GearMap m_gearMap;
	std::vector<int> m_gearRange;
};