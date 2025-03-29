#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): type("default")
{
	std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string name): type(name)
{
	std::cout << "WrongAnimal type " << type << " constructor called"  << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const & src)
{
	std::cout << "WrongAnimal copy constructor called" << std::endl;
	*this = src;
}

WrongAnimal & WrongAnimal::operator=(WrongAnimal const & src)
{
	if (this != &src)
		this->type = src.type;
	return *this;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal destructor called" << std::endl;
}

void WrongAnimal::makeSound(void) const
{
	std::cout << "generic sound" << std::endl;
}

std::string WrongAnimal::getType(void) const
{
	return this->type;
}