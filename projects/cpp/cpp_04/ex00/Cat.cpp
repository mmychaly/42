#include "Cat.hpp"

Cat::Cat(void): Animal("Cat")
{
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(Cat const & src): Animal(src)
{
	std::cout << "Cat copy constructor called" << std::endl;
//	*this = src;
}

Cat & Cat::operator=(Cat const & src)
{
	if (this != &src)
		this->type = src.type;
	return *this;
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound(void) const
{
	std::cout << "meoow meooowwww" << std::endl;
}