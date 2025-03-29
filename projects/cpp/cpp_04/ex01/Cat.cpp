#include "Cat.hpp"

Cat::Cat(void): Animal("Cat")
{
	std::cout << "Cat default constructor called" << std::endl;
	cat_brain = new Brain();
}

Cat::Cat(Cat const & src): Animal(src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	cat_brain = new Brain(*src.cat_brain);
//	*this = src;
}

Cat & Cat::operator=(Cat const & src)
{
	if (this != &src)
	{
		this->type = src.type;
		if (cat_brain)
			delete cat_brain;
		cat_brain = new Brain(*src.cat_brain);
	}
	return *this;
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor called" << std::endl;
	delete cat_brain;
}

void Cat::makeSound(void) const
{
	std::cout << "meoow meooowwww" << std::endl;
}

Brain* Cat::getCatBrain(void) const
{
	return cat_brain;
}