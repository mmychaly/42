#include "Weapon.hpp"

Weapon::Weapon(void)
{
	return ;
}
Weapon::Weapon(std::string str) : _type(str)
{
	return ;
}
Weapon::~Weapon(void)
{
	return ;
}

std::string const & Weapon::getType(void)
{
	return _type;
}
void Weapon::setType(std::string new_type)
{
	_type = new_type;
}