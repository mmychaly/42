#include "FragTrap.hpp"

FragTrap::FragTrap(void):ClapTrap()
{
	std::cout << "Defaul constructors of FragTrap called" << std::endl;
	std::cerr << "Error: you forget make name of FragTrap" << std::endl;
	this->_hit = 100;
	this->_energy = 100;
	this->_attack = 30;
}

FragTrap::FragTrap(std::string str): ClapTrap(str)
{
	std::cout << "Constructors of FragTrap " << str << " called" << std::endl;
	this->_hit = 100;
	this->_energy = 100;
	this->_attack = 30;
}

FragTrap::FragTrap(FragTrap const & src) : ClapTrap(src.get_name())
{
	std::cout << "Copy constructor of FragTrap " << src.get_name() << " called" << std::endl;
	*this = src;
}

FragTrap & FragTrap::operator=(FragTrap const & src)
{
	if (this != &src)
	{
		this->_name = src.get_name();
		this->_hit = src.get_hit();
		this->_energy = src.get_energy();
		this->_attack = src.get_attack();
	}
	return *this;
}

FragTrap::~FragTrap(void)
{
	std::cout << "Destructors of FragTrap " << this->get_name() << " called" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	if (this->get_energy() <= 0)
	{
		std::cout << "FragTrap " << this->get_name() << " dont have energy for high fives !" << std::endl;
		return;
	}
	if (this->get_hit() <= 0)
	{
		std::cout << "FragTrap " << this->get_name() << " dont have hit for high fives !" << std::endl;
		return;
	}
	std::cout << "FragTrap " << this->get_name() << " you wants high fives ?" << std::endl;
}