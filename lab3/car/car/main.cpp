#include "stdafx.h"
#include "Car.h"
#include "СarProcessor.h"

using namespace std;

int main(int, char *[])
{
	CCar car(cout);
	CarProcessor CarProcessor(car, cout);

	string action;
	cout << endl << ">";
	while (getline(cin, action))
	{
		CarProcessor.HandleCommand(action);
		cout << endl << ">";
	}
	return 0;
}