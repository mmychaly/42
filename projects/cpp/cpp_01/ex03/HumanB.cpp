#include "HumanB.hpp"


HumanB::HumanB(std::string str) : _name(str), _weapon(nullptr)
{
	return ;
}

HumanB::~HumanB(void)
{
	return ;
}
void HumanB::setWeapon(Weapon& new_w)
{
	_weapon = &new_w;
}

void HumanB::attack(void)
{
	if ( _weapon != NULL && _weapon->getType() != "" )
		std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
	else
		std::cout << "You need armed " << _name << std::endl;
}