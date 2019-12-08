/* Lab 6 - Company Employee Information
 * Purpose: Read a list of employees from a file and perform
 *          basic human resource operations
 * CSC2430 Winter 2018
 * Author: Max Briggs
 * 2018-3-27 */

/* includes */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
#include "employee.h"
#include "company.h"

void PrintMenu();
void LoadFile(Company& company);
void SaveData(Company& company);
void SearchName(Company& company);
void SearchId(Company& company);
void SearchBoss(Company& company);
void AddEmployee(Company& company);
void CheckFull(Company& company);

int main()
{
	bool quit = false;
	int selection;
	Company company;

	cout << setprecision(2) << fixed;

	do {
		PrintMenu();
		cin >> selection;
		while (cin.fail()) { /* error checking */
			cerr << "Invalid input, please try again\n";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> selection;
		}

		switch(selection) {
		case 1: /* Load Company file */
			LoadFile(company);
			break;
		case 2: /* Save Company Data to file */
			SaveData(company);
			break;
		case 3: /* List all employees */
			company.Write(cout);
			break;
		case 4: /* Search by Name */
			SearchName(company);
			break;
		case 5: /* Search by ID */
			SearchId(company);
			break;
		case 6: /* Find Employee Boss Information */
			SearchBoss(company);
			break;
		case 7: /* Add New Employee */
			AddEmployee(company);
			break;
		case 8: /* Check if full */
			CheckFull(company);
			break;
		case 9: /* Quit */
			quit = true;
			break;
		}
	} while(!quit);
	return 0;
}

/* Print out menu */
void PrintMenu()
{
	cout <<
		"1. Load a Company File\n" <<
		"2. Save Company Data to File\n" <<
		"3. List all Employees\n" <<
		"4. Search by Name\n" <<
		"5. Search by ID\n" <<
		"6. Find Employee Boss Information\n" <<
		"7. Add a New Employee\n" <<
		"8. Check if the Database is Full\n" <<
		"9. Exit\n";
}

/* Load company data file
 * Params: Company object */
void LoadFile(Company& company)
{
	string fileName;
	ifstream companyFile;

	cout << "Filename: ";
	cin >> fileName;
	companyFile.open(fileName);

	if (companyFile.fail()) {
		cerr << "Can't open \"" << fileName << "\"\n";
		return;
	}
	int numRead = company.Read(companyFile);
	cout << "File loaded, " << numRead << " records read\n";

	return;
}

/* Save company data to text file
 * Params: Company object */
void SaveData(Company& company)
{
	string fileName;

	cout << "Filename: ";
	cin >> fileName;
	ofstream companyFile (fileName, ios::out | ios::app | ios::binary);
	int numWritten = company.Write(companyFile);
	cout << numWritten << " employees written\n";
}

/* Search for all employees with entered name
 * Params: Company object */
void SearchName(Company& company)
{
	string name;
	int pos = 0;
	cout << "Searching all employees with name: ";
	cin >> name;
	do {
		pos = company.FindByName(name, pos);
		if (pos != -1) {
			Employee tmp(*company.Get(pos));
			cout << tmp.ToString();
		} else
			break;
		pos++;
	} while (true);
}

/* Search for employees by ID
 * Params: Company object */
void SearchId(Company& company)
{
	unsigned int id;

	cin >> id;
	while (cin.fail()) {
		cerr << "Invalid input, please try again\n";
		cin.clear();
		cin.ignore(255, '\n');
		cin >> id;
	}

	int pos = company.FindById(id);
	if (pos != -1) {
		Employee tmp(*company.Get(pos));
		cout << tmp.ToString();
	}
}

/* Search for employees by boss ID
 * and prints employee and boss's info
 * Params: Company object */
void SearchBoss(Company& company)
{
	unsigned int id;
	unsigned int managerId = 0;

	cin >> id;
	while (cin.fail()) { /* error check */
		cerr << "Invalid input, please try again\n";
		cin.clear();
		cin.ignore(255, '\n');
		cin >> id;
	}

	int pos = company.FindById(id);
	if (pos != -1) {
		Employee tmp(*company.Get(pos));
		managerId = tmp.GetManagerId();
		cout << "Employee current information:\n"
		     << tmp.ToString();
	}
	if (managerId != 0) {
		Employee tmp(*company.Get(managerId));
		cout << "Boss Information:\n"
		     << tmp.ToString();
	}
}

/* Add Employee to company database
 * Params:Company object */
void AddEmployee(Company& company)
{
	unsigned int id;
	string name;
	double salary;
	unsigned int bossId;
	if (!company.IsFull()) {
		/* ID input */
		cout << "Input Employee Information\n"
		     << "Employee ID: ";
		cin >> id;
		while(cin.fail()) {
			cerr << "Invalid input, please try again\n";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> id;
		}
		while(company.FindById(id) != -1) {
			cout << "ID already on file, choose a different ID: ";
			cin >> id;
			while(cin.fail()) {
				cerr << "Invalid input, please try again\n";
				cin.clear();
				cin.ignore(255, '\n');
				cin >> id;
			}
		}
		cout << "Employee Name: ";
		cin >> name;
		cout << "Salary: ";
		cin >> salary;
		while(cin.fail()) {
			cerr << "Invalid input, please try again\n";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> salary;
		}
		cout << "Boss ID (0 for none): ";
		cin >> bossId;
		while(cin.fail()) {
			cerr << "Invalid input, please try again\n";
			cin.clear();
			cin.ignore(255, '\n');
			cin >> bossId;
		}
		company.AddEmployee(id, name, salary, bossId);
		cout << name << " added successfully\n";
	} else
		cout << "Cannot add new records, database is full\n";
}

/* Check if database is full
 * Params: Company object */
void CheckFull(Company& company)
{
	if (company.IsFull())
		cout << "Database is Full\n";
	else
		cout << "Database is Not Full\n";
}

