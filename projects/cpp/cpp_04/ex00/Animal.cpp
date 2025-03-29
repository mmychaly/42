#include "Animal.hpp"

Animal::Animal(void): type("default")
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string name): type(name)
{
	std::cout << "Animal type " << type << " constructor called" << std::endl;
}

Animal::Animal(Animal const & src)
{
	std::cout << "Animal type " << src.type << " copy constructor called " << std::endl;
	*this = src;
}

Animal & Animal::operator=(Animal const & src)
{
	if (this != &src)
		this->type = src.type;
	return *this;
}

Animal::~Animal(void)
{
	std::cout << "Animal type " << type << " destructor called " << std::endl;
}

void Animal::makeSound(void) const
{
	std::cout << "Unidentifiable sound" << std::endl;
}

std::string Animal::getType(void) const
{
	return (this->type);
}