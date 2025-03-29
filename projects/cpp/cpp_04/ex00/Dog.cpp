#include "Dog.hpp"

Dog::Dog(void): Animal("Dog")
{
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(Dog const & src): Animal("Dog")
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = src;
}

Dog & Dog::operator=(Dog const & src)
{
	if (this != &src)
		this->type = src.type;
	return *this;
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
	std::cout << "RAF RAF" << std::endl;
}