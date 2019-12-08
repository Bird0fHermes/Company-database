const unsigned int MAX_EMPLOYEES = 10;
class Company
{
	public:
		Company();
		bool AddEmployee(
			unsigned int,
			const string&,
			double,
			unsigned int = 0);
		bool AddEmployee(const Employee&);
		int FindById(unsigned int) const;
		int FindByName(
			const string&,
			unsigned int = 0) const;
		int Read(istream&);
		int Write(ostream&) const;
		bool IsFull() const;
		Employee* Get(unsigned int) const;
		unsigned int GetEmployeeCount() const;
		~Company();
	private:
		Employee* _employee[MAX_EMPLOYEES];
		unsigned int _employeeCount;
		int BinarySearch(unsigned int) const;
		void Sort();
};
