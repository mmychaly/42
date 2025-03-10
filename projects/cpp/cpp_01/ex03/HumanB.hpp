#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
	public:
		HumanB(std::string str);
		~HumanB(void);
		void setWeapon(Weapon& new_w);
		void attack(void);

	private:
		Weapon* _weapon;
		std::string _name;
};
#endif