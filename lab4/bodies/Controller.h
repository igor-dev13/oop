#pragma once
#include <boost/noncopyable.hpp>

class CBody;

class CController : boost::noncopyable
{
public:
	CController(std::vector<std::shared_ptr<CBody>> & bodies, std::istream & input, std::ostream & output);
	bool HandleCommand();

	bool CController::Info() const;
	void GetAllBodies(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const;
	void GetBodyWithMaxMass(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const;
	void GetBodyWithMinWeightInWater(const std::vector<std::shared_ptr<CBody>> &bodies, std::ostream &strm) const;
	double GetBodyWeightInWater(const CBody &body) const;

private:	
	bool CreateSphere(std::istream & args);
	bool CreateParallelepiped(std::istream & args);
	bool CreateCone(std::istream & args);
	bool CreateCylinder(std::istream & args);
	bool CController::CreateCompound(std::istream &args);

private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	const ActionMap m_actionMap;	
	std::istream & m_input;
	std::ostream & m_output;	
	std::vector<std::shared_ptr<CBody>> & m_bodies;
};