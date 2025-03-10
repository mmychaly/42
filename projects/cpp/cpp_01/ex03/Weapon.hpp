#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

class Weapon
{
	public:
		Weapon(void);
		Weapon(std::string str);
		~Weapon(void);
	
		std::string const & getType(void);
		void setType(std::string new_type);

	private:
	std::string _type;
};

#endif