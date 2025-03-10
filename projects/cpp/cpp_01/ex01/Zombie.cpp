#include "Zombie.hpp"

Zombie::Zombie(void)
{
	return;
}

Zombie::Zombie(std::string str): _name(str)
{
	return;
}

Zombie::~Zombie(void)
{
	std::cout << "Called destructor for " << _name << std::endl;
}

void Zombie::announce(void)
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::set_name(std::string name)
{
	_name = name;
}