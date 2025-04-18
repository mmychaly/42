#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <climits>
class ClapTrap
{
	public:
		ClapTrap(void);
		ClapTrap(std::string str);
		ClapTrap(ClapTrap const & src);
		ClapTrap & operator=(ClapTrap const & src);
		~ClapTrap(void);

		std::string get_name(void) const;
		int get_hit(void) const;
		int get_energy(void) const;
		int get_attack(void) const;

		void set_add_hit(unsigned int hit_points);
		void set_left_hit(unsigned int hit_points);
		void set_energy(void);
		
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

	private:
		std::string _name;
		int _hit;
		int _energy;
		int _attack ;
};

//std::ostream & operator<<(std::ostream & out, ClapTrap const & src);

#endif