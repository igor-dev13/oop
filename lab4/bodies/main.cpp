#include "stdafx.h"
#include "Controller.h"

int main()
{
	std::vector<std::shared_ptr<CBody>> bodies;
	CController controller(bodies, std::cin, std::cout);
	controller.Info();

	while ((!std::cin.eof()) && (!std::cin.fail()))
	{
		std::cout << "> ";
		if (!controller.HandleCommand())
		{
			break;
		}
	}

	if (!bodies.empty())
	{
		controller.GetAllBodies(bodies, std::cout);
		controller.GetBodyWithMaxMass(bodies, std::cout);
		controller.GetBodyWithMinWeightInWater(bodies, std::cout);
	}
	else
	{
		std::cout << "Please enter correct geometric bodies." << std::endl;
	}

	return 0;
}

