#include "stdafx.h"
#include "Body.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Controller.h"

CController::CController(std::vector<std::shared_ptr<CBody>> & bodies, std::istream & input, std::ostream & output)
	: m_bodies(bodies)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "CreateSphere", std::bind(&CController::CreateSphere, this, std::placeholders::_1) },
		{ "CreateParallelepiped", std::bind(&CController::CreateParallelepiped, this, std::placeholders::_1) },
		{ "CreateCone", std::bind(&CController::CreateCone, this, std::placeholders::_1) },
		{ "CreateCylinder", std::bind(&CController::CreateCylinder, this, std::placeholders::_1) }
	})
{
}

bool CController::HandleCommand()
{
	std::string commandLine;

	if ((!std::getline(m_input, commandLine)) || (commandLine.empty()))
	{
		return true;
	}
	else if (commandLine == "...")
	{
		return false;
	}

	std::istringstream strm(commandLine);
	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		try
		{
			it->second(strm);
		}
		catch (const std::invalid_argument &error)
		{
			m_output << error.what() << '\n';
		}
	}
	else
	{
		m_output << "Unknown command!\n";
	}

	return true;
}

bool CController::CreateSphere(std::istream &args)
{
	bool created = false;
	double parametr;
	std::vector<double> parametrs;
	while (args >> parametr)
	{
		parametrs.push_back(parametr);
	}

	if (parametrs.size() == 2)
	{
		std::shared_ptr<CBody> ptr = std::make_shared<CSphere>(parametrs.at(0), parametrs.at(1));
		m_bodies.push_back(ptr);
		created = true;
		m_output << "Sphere created.\n";
	}
	else
	{
		m_output << "Can't create this sphere.\n"
			<< "Try: CreateSphere density, radius\n";
	}

	return created;
}

bool CController::CreateParallelepiped(std::istream &args)
{
	bool created = false;
	double parametr;
	std::vector<double> parametrs;
	while (args >> parametr)
	{
		parametrs.push_back(parametr);
	}

	if (parametrs.size() == 4)
	{
		std::shared_ptr<CBody> ptr = std::make_shared<CParallelepiped>(parametrs.at(0), parametrs.at(1), parametrs.at(2), parametrs.at(3));
		m_bodies.push_back(ptr);
		created = true;
		m_output << "Parallelepiped created.\n";
	}
	else
	{
		m_output << "Can't create parallelepiped.\n"
			<< "Try: CreateParallelepiped density, width, height, depth\n";
	}

	return created;
}

bool CController::CreateCone(std::istream &args)
{
	bool created = false;
	double parametr;
	std::vector<double> parametrs;
	while (args >> parametr)
	{
		parametrs.push_back(parametr);
	}

	if (parametrs.size() == 3)
	{
		std::shared_ptr<CBody> ptr = std::make_shared<CCone>(parametrs.at(0), parametrs.at(1), parametrs.at(2));
		m_bodies.push_back(ptr);
		created = true;
		m_output << "Cone created.\n";
	}
	else
	{
		m_output << "Can't create this cone.\n"
			<< "Try: CreateCone density, ,base radius, height\n";
	}

	return created;
}

bool CController::CreateCylinder(std::istream &args)
{
	bool created = false;
	double parametr;
	std::vector<double> parametrs;
	while (args >> parametr)
	{
		parametrs.push_back(parametr);
	}

	if (parametrs.size() == 3)
	{
		std::shared_ptr<CBody> ptr = std::make_shared<CCylinder>(parametrs.at(0), parametrs.at(1), parametrs.at(2));
		m_bodies.push_back(ptr);
		created = true;
		m_output << "Cylinder created.\n";
	}
	else
	{
		m_output << "Can't create this cylinder.\n"
			<< "Try: CreateCylinder density, base radius, height\n";
	}

	return created;
}

void CController::GetAllBodies(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
	if (!bodies.empty())
	{
		for (const auto &body : bodies)
		{
			strm << body->ToString() << '\n';
		}
	}
}

void CController::GetBodyWithMaxMass(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
	if (!bodies.empty())
	{
		auto IsWeightBigger = [](const std::shared_ptr<CBody> &first, const std::shared_ptr<CBody> &second)
		{
			return (first->GetMass() < second->GetMass());
		};

		auto bodyMaxMass = *std::max_element(bodies.begin(), bodies.end(), IsWeightBigger);

		strm << "Body with max mass is " << bodyMaxMass->ToString() << '\n';
	}
}

void CController::GetBodyWithMinWeightInWater(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const
{
	if (!bodies.empty())
	{
		auto IsWeightLess = [this](const std::shared_ptr<CBody> &first, const std::shared_ptr<CBody> &second)
		{
			return (GetBodyWeightInWater(*first) < GetBodyWeightInWater(*second));
		};

		auto bodyWithMinWeightInWater = *std::min_element(bodies.begin(), bodies.end(), IsWeightLess);

		strm << "Body with min weight in water is " << bodyWithMinWeightInWater->ToString() << '\n';
	}
}

double CController::GetBodyWeightInWater(const CBody &body) const
{
	// ускорение свободного падения
	const double gravityResistance = 9.8;
	const double waterDensity = 1000;

	return gravityResistance * body.GetVolume() * (body.GetDensity() - waterDensity);
}

bool CController::Info() const
{
	m_output << "possible commands:\n"
		<< "1. CreateSphere density, radius\n"
		<< "2. CreateParallelepiped width, height, depth, density\n"
		<< "3. CreateCone density, radius, height\n"
		<< "4. CreateCylinder density, radius, height\n"
		<< "... - end entering elements of compound body or exit\n";
	return true;
}