#include "Brain.hpp"

Brain::Brain(void)
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(Brain const & src)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = src;
}

Brain & Brain::operator=(Brain const & src)
{
	if (this != &src)
	{
		for (int i = 0; i < 100; i++)
		{
			this->ideas[i] = src.ideas[i];
		}
	}
	return *this;
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called" << std::endl;
}

const std::string* Brain::get_all_ideas(void)
{
	return ideas;
}

std::string Brain::get_idea(int index)
{
	if (index < 0 || index >= 100)
	{
		std::cout << "index outside of range" << std::endl;
		return "";
	}
	return ideas[index];
}
void Brain::set_idea(std::string str)
{
	for (int i = 0; i < 100; i++)
	{
		if (ideas[i].empty())
		{
			ideas[i] = str;
			return;
		}
	}
	std::cout << "Brain is full, cannot add more ideas" << std::endl;
}