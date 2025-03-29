#include "../includes/Cure.hpp"
#include <string>
#include <iostream>

Cure::Cure(void): AMateria("cure")
{
	std::cout << "Cure default constructor called" << std::endl;
}

Cure::Cure(Cure const & src): AMateria("cure")
{
	std::cout << "Cure copy constructor called" << std::endl;
	*this = src; 
}

Cure::~Cure(void)
{
	std::cout << "Cure destructor called" << std::endl;
}

Cure & Cure::operator=(Cure const & src)
{
	if (this != &src)
		this->_type = src._type;
	return *this;
}

// std::string const & Cure::getType() const
// {
// 	return this->_type;
// }

AMateria* Cure::clone(void) const
{
	AMateria* temp = new Cure();
	return temp;
}

void Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}