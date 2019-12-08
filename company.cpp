/* includes */
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

#include "employee.h"
#include "company.h"

/* Company default constructor
 * Sets number of employees to 0 */
Company::Company()
{
	_employeeCount = 0;
}

/* Add employee
 * Params: id, name, salary, manager id
 * Returns: True if there is space to add employee into company database */
bool Company::AddEmployee(unsigned int id, const string& name, double salary, unsigned int managerId)
{
	if (!IsFull()) {
		_employee[_employeeCount] = new Employee(id, name, salary, managerId);
		_employeeCount++;
		return true;
	} else
		return false;
}

/* Add employee
 * Params: Employee object
 * Returns: true if there is space to add employee into company database */
bool Company::AddEmployee(const Employee& employee)
{
	if (!IsFull()) {
		_employee[_employeeCount] = new Employee(employee);
		_employeeCount++;
		return true;
	} else
		return false;
}

/* Search employee by id number
 * Params: id number
 * Returns: index of employee if found, -1 if not */
int Company::FindById(unsigned int id) const
{
	int index = BinarySearch(id);
	
	if (index != -1)
		return index;
	else
		return -1;
}

/* Search employee by name
 * Params: name, position to search from
 * Returns: position of employee if found, -1 if not */
int Company::FindByName(const string& name, unsigned int position) const
{
	for (unsigned int i = position; i < _employeeCount; i++)
		if (name == _employee[i]->GetName())
			return i;
	return -1;
}

/* Read employee data into database
 * Params: input stream of employee data
 * Returns: number of employees read */
int Company::Read(istream& employeeData)
{
	unsigned int position = _employeeCount;
	int numRead = 0;

	unsigned int id;
	string name;
	double salary;
	unsigned int managerId;

	employeeData >> id >> name >> salary >> managerId;

	while (position < MAX_EMPLOYEES && !employeeData.fail()) {
		AddEmployee(id, name, salary, managerId);
		position++;
		numRead++;
		employeeData >> id >> name >> salary >> managerId;
	}

	Sort();

	return numRead;
}

/* Write employee data to output buffer
 * Params: output stream to write to
 * Returns: number of employees written */
int Company::Write(ostream& buffer) const
{
	int numWritten = 0;

	for (unsigned int a = 0; a < _employeeCount; a++) {
		_employee[a]->Write(buffer);
		buffer << '\n';
		numWritten++;
	}

	return numWritten;

}

/* Determine if database is full
 * Returns: true if database is full */
bool Company::IsFull() const
{
	if (MAX_EMPLOYEES == _employeeCount)
		return true;
	else
		return false;
}

/* Get pointer to employee
 * Params: index
 * Returns: pointer to employee if in database, NULL if not */
Employee* Company::Get(unsigned int index) const

{
	if (index < _employeeCount)
		return _employee[index];
	else
		return NULL;
}

/* Get count of employees
 * Returns: count of employees */
unsigned int Company::GetEmployeeCount() const
{
	return _employeeCount;
}

/* Company destructor */
Company::~Company()
{
	for (unsigned int a = 0; a < _employeeCount; a++) {
		delete _employee[a];
		_employee[a] = NULL;
	}
}

/* Binary search
 * Params: id number to search for
 * Returns: index of searched key if found, -1 if no */
int Company::BinarySearch(unsigned int key) const
{
	int first = 0;
	int last = _employeeCount - 1; /* calculate once */

	while(first <= last) {
		int mid = (first + last) / 2;
		unsigned int midId = _employee[mid]->GetId(); /* calculate once */
		if (key < midId)
			last = mid - 1;
		else if (key > midId)
			first = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* Bubble sort */
void Company::Sort()
{
	bool exchangeMade = true;

	for (unsigned int pass = 1; pass < _employeeCount; pass++) {
		exchangeMade = false;
		/* on each pass the range of elements decreases by 1 */
		for (unsigned int index = 0; index < _employeeCount - pass; index++)
			if (_employee[index]->GetId() > _employee[index + 1]->GetId()) {
				Employee tmp(*_employee[index]);
				*_employee[index] = *_employee[index + 1];
				*_employee[index + 1] = tmp;
				exchangeMade = true;
			}
	}
}

