#include <iostream>

class Pers
{
	private:
	int _age;
	std::string _name;

	public:

	Pers(int new_age, std::string new_name) : _age(new_age), _name(new_name)
	{
		std::cout << "Constructor called" << std::endl;
	}

	int get_Age(void) const
	{
		return _age;
	}

	std::string get_Name(void) const
	{
		return _name;
	}

	void set_Age(int age_new)
	{
		_age = age_new;
	}

	~Pers(void)
	{
		std::cout << "Destructor called" << std::endl;
	}
};


int main(void)
{
	Pers first(30, "Mike");
	std::cout << "name " << first.get_Name() << std::endl;
	std::cout << "begginer age " << first.get_Age() << std::endl;
	first.set_Age(33);
	std::cout << "after age " << first.get_Age() << std::endl;
	return (0);
}