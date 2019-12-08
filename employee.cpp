/* includes */
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#include "employee.h"

/* Employee constructor
 * Params: id number, name, salary and boss id */
Employee::Employee(unsigned int id, const string& name, double salary, unsigned int managerId)
{
	_id = id;
	if (!name.empty())
		_name = name;
	else
		_name = "***";
	_salary = salary;
	_managerId = managerId;
}

/* Employee copy constructor
 * Params: Employee object to copy */
Employee::Employee(const Employee& toCopy)
{
	_id = toCopy.GetId();
	_name = toCopy.GetName();
	_salary = toCopy.GetSalary();
	_managerId = toCopy.GetManagerId();
}

/* Get employee id
 * Returns: _id */
unsigned int Employee::GetId() const
{
	return _id;
}

/* Get employee name
 * Returns: _name */
string Employee::GetName() const
{
	return _name;
}

/* Get employee salary
 * Returns: _salary */
double Employee::GetSalary() const
{
	return _salary;
}

/* Get employee boss id
 * Returns: _managerId */
unsigned int Employee::GetManagerId() const
{
	return _managerId;
}

/* Print out all employee info
 * Returns: string of all employee info */
string Employee::ToString() const
{
	stringstream outStream;
	string outString;

	outStream << setprecision(2) << fixed;

	outStream << "Name: " << left << setw(10) << _name 
		  << " ID: " << right << setw(5) << _id
		  << " Salary: " << setw(10) << _salary
		  << " Manager ID: " << setw(5) << _managerId << '\n';

	outString = outStream.str();

	return outString;
}

/* Give employee raise */
void Employee::Raise(double raiseNum)
{
	_salary += raiseNum;
}

/* Compare two employees
 * Params: Employee to compare
 * Returns: true if they are the same, false if not */
bool Employee::Equals(const Employee& compared) const
{
	if (_id == compared.GetId() && _name == compared.GetName() && _salary == compared.GetSalary() && _managerId == compared.GetManagerId())
		return true;
	else
		return false;
}

/* Read employee info from istream into employee
 * Params: input stream
 * Returns: true if read, false if not */
bool Employee::Read(istream& inEmployee)
{
	inEmployee >> _id >> _name >> _salary >> _managerId; /* read in */

	/* error checking */
	if (!inEmployee.fail())
		return true;
	else
		return false;
}

/* Output employee info to output stream
 * Params: output stream */
void Employee::Write(ostream& outEmployee) const
{
	outEmployee << _id << ' ' << _name << ' ' << _salary << ' ' << _managerId;
}

/* Employee destructor */
Employee::~Employee()
{
}

