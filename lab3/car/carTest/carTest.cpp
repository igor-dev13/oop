#include "stdafx.h"
#include "../car/Car.h"
#include <functional>

using namespace std;
using namespace std::placeholders;

struct CarDependencies
{
	stringstream output;
};

struct CarFixture : CarDependencies
{
	CCar car;

	CarFixture()
		: car(output)
	{
	}

	void CarsAreEqual(const CCar & car1, const CCar & car2)
	{
		BOOST_CHECK(car1.GetDirection() == car2.GetDirection());
		BOOST_CHECK(car1.GetGear() == car2.GetGear());
		BOOST_CHECK(car1.GetSpeed() == car2.GetSpeed());
	}

	void CheckCarState(Gear expectedGear, int expectedSpeed, Direction expectedDirection)
	{		
		BOOST_CHECK(car.GetSpeed() == expectedSpeed);
		BOOST_CHECK(car.GetGear() == expectedGear);
		BOOST_CHECK(car.GetDirection() == expectedDirection);
	}

	void CanSetSpeed(int speed)
	{
		BOOST_CHECK(car.SetSpeed(speed));
		CheckCarState(car.GetGear(), speed, car.GetDirection());
	}

	void CantSetSpeed(int speed)
	{
		CCar carClone = car;
		BOOST_CHECK(!car.SetSpeed(speed));
		CarsAreEqual(car, carClone);
	}

	void CanSetGear(Gear gear)
	{
		BOOST_CHECK(car.SetGear(gear));
		CheckCarState(gear, car.GetSpeed(), car.GetDirection());
	}

	void CantSetGear(Gear gear)
	{
		CCar carClone = car;
		BOOST_CHECK(!car.SetGear(gear));
		CarsAreEqual(car, carClone);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(engine_can_be_switched_on_by_default)
		{
			BOOST_CHECK(car.TurnOnEngine());
			CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(engine_can_be_switched_on_and_then_can_be_switched_off_by_default)
		{
			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.TurnOffEngine());
			CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(engine_is_switched_off)
		BOOST_AUTO_TEST_CASE(engine_must_have_turned_off_emgine)
		{
			BOOST_CHECK(!car.IsEngineOn());
			CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(gear_must_have_neutral_when_engine_turned_off)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		BOOST_AUTO_TEST_CASE(car_must_have_stop_direction_when_engine_turned_off)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(car_must_have_zero_speed_when_engine_turned_off)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(cant_set_speed_when_engine_turned_off)
		{
			CantSetSpeed(10);
		}
		BOOST_AUTO_TEST_CASE(can_set_gear_only_on_neutral_when_engine_turned_off)
		{
			CantSetGear(Gear::FIRST);
			CanSetGear(Gear::NEUTRAL);
		}
	BOOST_AUTO_TEST_SUITE_END()

		
	struct engine_switched_on_ : CarFixture
	{
		engine_switched_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(engine_is_switched_on, engine_switched_on_)
		BOOST_AUTO_TEST_CASE(car_must_have_zero_speed_when_engine_is_switched_on)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(cant_set_speed_when_engine_is_switched_on)
		{
			CantSetSpeed(10);
		}
		BOOST_AUTO_TEST_CASE(car_must_have_no_direction_when_engine_is_switched_on)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(car_must_have_neutral_gear_when_engine_is_switched_on)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		BOOST_AUTO_TEST_CASE(car_can_reach_maximum_speed_value_when_engine_is_switched_on)
		{
			CanSetGear(Gear::FIRST);
			CanSetSpeed(30);
			CanSetGear(Gear::SECOND);
			CanSetSpeed(40);
			CanSetGear(Gear::THIRD);
			CanSetSpeed(60);
			CanSetGear(Gear::FOURTH);
			CanSetSpeed(90);
			CanSetGear(Gear::FIFTH);
			CanSetSpeed(150);
			CheckCarState(Gear::FIFTH, 150, Direction::FORWARD);
		}
		BOOST_AUTO_TEST_CASE(can_increase_speed_switch_on_neutral_gear_and_stop_when_engine_is_switched_on)
		{
			CanSetGear(Gear::FIRST);
			CanSetSpeed(20);
			CheckCarState(Gear::FIRST, 20, Direction::FORWARD);
			CanSetGear(Gear::NEUTRAL);
			CanSetSpeed(0);
			CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
	BOOST_AUTO_TEST_SUITE_END()

		
	struct neutral_gear_is_switched_on_ : engine_switched_on_
	{
		neutral_gear_is_switched_on_()
		{
			car.SetGear(Gear::NEUTRAL);
		}
	};
	
	BOOST_FIXTURE_TEST_SUITE(neutral_gear_is_switched_on, neutral_gear_is_switched_on_)
		BOOST_AUTO_TEST_CASE(cant_increase_a_speed_when_neutral_gear_is_switched_on)
		{
			CantSetSpeed(10);
		}

	BOOST_AUTO_TEST_SUITE_END()

		
	struct first_gear_is_switched_on_ : engine_switched_on_
	{
		first_gear_is_switched_on_()
		{
			car.SetGear(Gear::FIRST);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(first_gear_is_switched_on, first_gear_is_switched_on_)
		BOOST_AUTO_TEST_CASE(can_switch_on_third_gear_when_speed_is_30_and_first_gear_is_switched_one)
		{
			CanSetSpeed(30);
			BOOST_CHECK(car.GetSpeed() == 30);
			CanSetGear(Gear::THIRD);
			CheckCarState(Gear::THIRD, 30, Direction::FORWARD);
		}
	
		BOOST_AUTO_TEST_CASE(can_switch_gear_to_neutral_when_first_gear_is_switched_on)
		{
			CanSetGear(Gear::NEUTRAL);
			CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
		
		BOOST_AUTO_TEST_CASE(can_switch_gear_to_second_when_speed_is_20_and_first_gear_is_switched_on)
		{
			CanSetSpeed(20);
			CanSetGear(Gear::SECOND);
			CheckCarState(Gear::SECOND, 20, Direction::FORWARD);
		}

		BOOST_AUTO_TEST_CASE(cant_increase_speed_more_then_gear_speed_range_allowed_and_first_gear_is_switched_on)
		{					
			CantSetSpeed(31);
		}
		BOOST_AUTO_TEST_CASE(cant_switch_on_reverse_gear_when_speed_more_then_zero_and_first_gear_is_switched_on)
		{
			CanSetSpeed(20);
			CheckCarState(Gear::FIRST, 20, Direction::FORWARD);
			CantSetGear(Gear::REVERSE);
		}

	BOOST_AUTO_TEST_SUITE_END()

		
	struct reverse_gear_is_switched_on_ : engine_switched_on_
	{
		reverse_gear_is_switched_on_()
		{
			car.SetGear(Gear::REVERSE);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(reverse_gear_is_switched_on, reverse_gear_is_switched_on_)
		BOOST_AUTO_TEST_CASE(can_increase_speed_and_then_decrease_speed_when_reverse_gear_is_switched_on)
		{
			CanSetSpeed(20);
			CanSetSpeed(10);
			CheckCarState(Gear::REVERSE, 10, Direction::BACK);
		}
		BOOST_AUTO_TEST_CASE(can_increase_speed_switch_on_neutral_and_decrease_speed_when_reverse_gear_is_switched_on)
		{
			CanSetSpeed(20);
			CanSetGear(Gear::NEUTRAL);
			CheckCarState(Gear::NEUTRAL, 20, Direction::BACK);
			CanSetSpeed(0);
			CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(cant_switch_on_first_gear_when_speed_more_then_zero_when_reverse_gear_is_switched_on)
		{
			CanSetSpeed(20);
			CheckCarState(Gear::REVERSE, 20, Direction::BACK);
			CantSetGear(Gear::FIRST);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct second_gear_is_switched_on_ : first_gear_is_switched_on_
	{
		second_gear_is_switched_on_()
		{
			car.SetSpeed(20);
			car.SetGear(Gear::SECOND);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(second_gear_is_switched_on, second_gear_is_switched_on_)
		BOOST_AUTO_TEST_CASE(can_switch_gear_to_neutral_when_second_gear_is_switched_on)
		{
			CanSetGear(Gear::NEUTRAL);
			CheckCarState(Gear::NEUTRAL, 20, Direction::FORWARD);
		}

		BOOST_AUTO_TEST_CASE(can_switch_gear_to_third_when_speed_is_40_and_second_gear_is_switched_on)
		{
			CanSetSpeed(40);
			CanSetGear(Gear::THIRD);
			CheckCarState(Gear::THIRD, 40, Direction::FORWARD);
		}

		BOOST_AUTO_TEST_CASE(can_reach_maximum_speed_in_gear_range_when_second_gear_is_switched_on)
		{
			CanSetSpeed(50);
		}

		BOOST_AUTO_TEST_CASE(can_reach_minimum_speed_in_gear_range_when_second_gear_is_switched_on)
		{
			CanSetSpeed(20);
		}

		BOOST_AUTO_TEST_CASE(cant_increase_speed_more_then_gear_speed_range_allowed_and_second_gear_is_switched_on)
		{
			CantSetSpeed(51);
		}

		BOOST_AUTO_TEST_CASE(cant_decrease_speed_more_then_gear_speed_range_allowed_and_second_gear_is_switched_on)
		{
			CantSetSpeed(19);
		}	

	BOOST_AUTO_TEST_SUITE_END()

		struct fifth_gear_is_switched_on_ : second_gear_is_switched_on_
		{
			fifth_gear_is_switched_on_()
			{
				car.SetSpeed(50);
				car.SetGear(Gear::THIRD);
				car.SetSpeed(60);
				car.SetGear(Gear::FOURTH);
				car.SetSpeed(90);
				car.SetGear(Gear::FIFTH);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(fifth_gear_is_switched_on, fifth_gear_is_switched_on_)
			BOOST_AUTO_TEST_CASE(can_switch_gear_to_neutral_when_fifth_gear_is_switched_on)
			{
				CanSetGear(Gear::NEUTRAL);
				CheckCarState(Gear::NEUTRAL, 90, Direction::FORWARD);
			}

			BOOST_AUTO_TEST_CASE(can_reach_maximum_speed_in_gear_range_when_fifth_gear_is_switched_on)
			{
				CanSetSpeed(150);
			}

			BOOST_AUTO_TEST_CASE(can_reach_minimum_speed_in_gear_range_when_fifth_gear_is_switched_on)
			{
				CanSetSpeed(50);
			}

			BOOST_AUTO_TEST_CASE(cant_increase_speed_more_then_gear_speed_range_allowed_and_fifth_gear_is_switched_on)
			{
				CantSetSpeed(151);
			}

			BOOST_AUTO_TEST_CASE(cant_decrease_speed_more_then_gear_speed_range_allowed_and_fifth_gear_is_switched_on)
			{
				CantSetSpeed(49);
			}

	BOOST_AUTO_TEST_SUITE_END()
	

BOOST_AUTO_TEST_SUITE_END()
