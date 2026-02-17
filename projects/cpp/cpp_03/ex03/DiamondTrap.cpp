#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void): ClapTrap(), ScavTrap(), FragTrap()
{
	std::cout << "Defaul constructors of DiamondTrap called" << std::endl;
	std::cerr << "Error: you forget make name of DiamondTrap" << std::endl;
	this->_attack = FragTrap::_attack;
	this->_energy = ScavTrap::_energy;
	this->_hit = FragTrap::_hit;
}
DiamondTrap::DiamondTrap(std::string str):ClapTrap(str + "_clap_name"), ScavTrap(), FragTrap()
{
	std::cout << "Constructors of DiamondTrap " << str << " called" << std::endl;
	std::cout << "this->_energy " << this->get_energy() << std::endl;
	this->_attack = FragTrap::_attack;
	this->_energy = ScavTrap::_energy;
	this->_hit = FragTrap::_hit;
}
DiamondTrap::DiamondTrap(DiamondTrap const & src): ClapTrap(src.get_name()), ScavTrap(src.get_name()), FragTrap(src.get_name())
{
	std::cout << "Copy constructor of DiamondTrap " << src.get_name() << " called" << std::endl;
	*this = src;
}
DiamondTrap::~DiamondTrap(void)
{
	std::cout << "Destructors of DiamondTrap " << this->get_name() << " called" << std::endl;
}

DiamondTrap & DiamondTrap::operator=(DiamondTrap const & src)
{
	if (this != &src)
	{
		this->_name = src.get_name();
		this->_attack = src.get_attack();
		this->_energy = src.get_energy();
		this->_hit = src.get_hit();
	}
	return *this;
}

void DiamondTrap::whoAmI(void)
{
	std::cout << "DiamondTrap name is " << _name << "ClapTrap name is " << ClapTrap::_name << std::endl;
}