#include "../includes/ICharacter.hpp"
#include "../includes/AMateria.hpp"
#include <string>
#include <iostream>

AMateria::AMateria(void): _type("default")
{
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const & _type): _type(_type)
{
	std::cout << "AMateria " << _type << " constructor called" << std::endl;
}

AMateria::AMateria(AMateria const & src)
{
	std::cout << "AMateria copy constructor called" << std::endl;
	*this = src; 
}

AMateria::~AMateria(void)
{
	std::cout << "AMateria destructor called" << std::endl;
}

AMateria & AMateria::operator=(AMateria const & src)
{
	if (this != &src)
		this->_type = src._type;
	return *this;
}

std::string const & AMateria::getType(void) const
{
	return _type;
}

void AMateria::use(ICharacter& target)
{
	std::cout << "_type : message for "<< target.getName() << std::endl;
}