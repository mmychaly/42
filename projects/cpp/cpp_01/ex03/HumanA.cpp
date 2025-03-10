#include "HumanA.hpp"


HumanA::HumanA(std::string name, Weapon& new_w) : _name(name), _weapon(new_w)
{
	return ;
}
HumanA::~HumanA(void)
{
	return ;
}
void HumanA::attack(void)
{
	if (_weapon.getType() == "")
		std::cout << "You need armed " << _name << std::endl;
	else
		std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}
