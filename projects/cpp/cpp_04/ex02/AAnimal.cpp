#include "AAnimal.hpp"

AAnimal::AAnimal(void): type("default")
{
	std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(std::string name): type(name)
{
	std::cout << "AAnimal type " << type << " constructor called" << std::endl;
}

AAnimal::AAnimal(AAnimal const & src)
{
	std::cout << "AAnimal type " << src.type << " copy constructor called " << std::endl;
	*this = src;
}

AAnimal & AAnimal::operator=(AAnimal const & src)
{
	if (this != &src)
		this->type = src.type;
	return *this;
}

AAnimal::~AAnimal(void)
{
	std::cout << "AAnimal type " << type << " destructor called " << std::endl;
}

/*void AAnimal::makeSound(void) const
{
	std::cout << "Unidentifiable sound" << std::endl;
}*/

std::string AAnimal::getType(void) const
{
	return (this->type);
}