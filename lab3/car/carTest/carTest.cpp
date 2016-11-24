#include "stdafx.h"
#include "../car/car.h"
#include <functional>

using namespace std;
using namespace std::placeholders;

// экземпляр для тестов
struct CarFixture
{
	CCar car;

	void ExpectFailure(std::function<bool(CCar & car)> const& action)
	{
		auto clone(car);
		BOOST_CHECK(!action(clone));
		BOOST_CHECK(car == clone);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(engine_can_be_switched_on)
		{
			BOOST_CHECK(car.TurnOnEngine());
		}
	BOOST_AUTO_TEST_CASE(engine_can_be_switched_on_and_then_can_be_switched_off)
	{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.TurnOffEngine());
	}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(when_switched_off_engine)
		BOOST_AUTO_TEST_CASE(engine_turned_off_initially)
		{
			BOOST_CHECK(!car.GetEngineStatus());
		}
		BOOST_AUTO_TEST_CASE(gear_is_neutral_initially)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		BOOST_AUTO_TEST_CASE(has_stop_direction)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(has_zero_speed)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(cant_set_speed)
		{
			{
				ExpectFailure([](auto & car) { return car.SetSpeed(10); });
			}
		}
		BOOST_AUTO_TEST_CASE(can_set_gear_only_on_neutral)
		{
			{
				ExpectFailure([](auto & car) { return car.SetGear(Gear::FIRST); });
			}

			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			}
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
		BOOST_AUTO_TEST_CASE(has_zero_speed)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(cant_set_negative_speed)
		{
			ExpectFailure([](auto & car) { return car.SetSpeed(-5); });
		}
		BOOST_AUTO_TEST_CASE(has_no_direction)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(car_is_in_neutral_gear)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
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
		BOOST_AUTO_TEST_CASE(cant_increase_a_speed)
		{
			{
				ExpectFailure([](auto & car) { return car.SetSpeed(5); });
			}
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
		BOOST_AUTO_TEST_CASE(can_increase_speed_and_switch_on_third_gear)
		{
			BOOST_CHECK(car.SetSpeed(30));
			BOOST_CHECK(car.SetGear(Gear::THIRD));
		}
		BOOST_AUTO_TEST_CASE(can_reach_maximum_speed_value)
		{
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(car.SetGear(Gear::SECOND));
			BOOST_CHECK(car.SetSpeed(40));
			BOOST_CHECK(car.SetGear(Gear::THIRD));
			BOOST_CHECK(car.SetSpeed(60));
			BOOST_CHECK(car.SetGear(Gear::FOURTH));
			BOOST_CHECK(car.SetSpeed(90));
			BOOST_CHECK(car.SetGear(Gear::FIFTH));
			BOOST_CHECK(car.SetSpeed(150));
		}
		BOOST_AUTO_TEST_CASE(can_increase_speed_switch_on_neutral_gear_and_decrease_speed)
		{
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.SetSpeed(0));			
		}
		BOOST_AUTO_TEST_CASE(cant_increase_speed_more_then_gear_speed_range_allowed)
		{					
			{
				ExpectFailure([](auto & car) { return car.SetSpeed(50); });
			}		
		}
		BOOST_AUTO_TEST_CASE(cant_switch_on_reverse_gear_when_speed_more_then_zero)
		{
			{
				BOOST_CHECK(car.SetSpeed(20));
			}
			{
				ExpectFailure([](auto & car) { return car.SetGear(Gear::REVERSE); });
			}
			{				
				BOOST_CHECK(car.SetSpeed(0));
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
			}
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
		BOOST_AUTO_TEST_CASE(can_increase_speed_and_then_decrease_speed)
		{
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(car.SetSpeed(10));
		}
		BOOST_AUTO_TEST_CASE(can_increase_speed_switch_on_neutral_and_decrease_speed)
		{
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.SetSpeed(0));
		}
		BOOST_AUTO_TEST_CASE(cant_switch_on_first_gear_when_speed_more_then_zero)
		{
			{
				BOOST_CHECK(car.SetSpeed(20));
			}
			{
				ExpectFailure([](auto & car) { return car.SetGear(Gear::FIRST); });
			}
			{
				BOOST_CHECK(car.SetSpeed(0));
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				BOOST_CHECK(car.GetGear() == Gear::FIRST);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()