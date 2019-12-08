class Employee
{
	public:
		Employee(
			unsigned int,
		       	const string&,
		       	double,
		       	unsigned int = 0);
		Employee(const Employee&);
		unsigned int GetId() const;
		string GetName() const;
		double GetSalary() const;
		unsigned int GetManagerId() const;
		string ToString() const;
		void Raise(double);
		bool Equals(const Employee&) const;
		bool Read(istream&);
		void Write(ostream&) const;
		~Employee();
	private:
		unsigned int _id;
		string _name;
		double _salary;
		unsigned int _managerId;
};
