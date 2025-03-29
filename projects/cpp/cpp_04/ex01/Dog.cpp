#include "Dog.hpp"

Dog::Dog(void): Animal("Dog")
{
	std::cout << "Dog default constructor called" << std::endl;
	dog_brain = new Brain();
}

Dog::Dog(Dog const & src): Animal("Dog")
{
	std::cout << "Dog copy constructor called" << std::endl;
	dog_brain = new Brain(*src.dog_brain);
	*this = src;
}

Dog & Dog::operator=(Dog const & src)
{
	if (this != &src)
	{
		this->type = src.type;
		if (dog_brain)
			delete dog_brain;
		dog_brain = new Brain(*src.dog_brain);
	}
	return *this;
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called" << std::endl;
	delete dog_brain;
}

void Dog::makeSound(void) const
{
	std::cout << "RAF RAF" << std::endl;
}

Brain* Dog::getDogBrain(void) const
{
	return dog_brain;
}