#include "../includes/Ice.hpp"
#include <string>
#include <iostream>

Ice::Ice(void): AMateria("ice")
{
	std::cout << "Ice default constructor called" << std::endl;
}

Ice::Ice(Ice const & src): AMateria("ice")
{
	std::cout << "Ice copy constructor called" << std::endl;
	*this = src; 
}

Ice::~Ice(void)
{
	std::cout << "Ice destructor called" << std::endl;
}

Ice & Ice::operator=(Ice const & src)
{
	if (this != &src)
		this->_type = src._type;
	return *this;
}

// std::string const & Ice::getType() const
// {
// 	return this->_type;
// }

AMateria* Ice::clone(void) const
{
	AMateria* temp = new Ice();
	return temp;
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}