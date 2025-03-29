#include "WrongCat.hpp"

WrongCat::WrongCat(void): WrongAnimal("WrongCat")
{
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(WrongCat const & src): WrongAnimal("WrongCat")
{
	std::cout << "WrongCat copy constructor called" << std::endl;
	*this = src;
}

WrongCat & WrongCat::operator=(WrongCat const & src)
{
	if (this != &src)
		this->type = src.type;
	return *this;
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound(void) const
{
	std::cout << "Miaou Miaou" << std::endl;
}