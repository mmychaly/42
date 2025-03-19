#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap bob("Bob");
	bob.attack("YOU");
	bob.takeDamage(3);
	bob.beRepaired(1);
	bob.beRepaired(1);
	std::cout << "Bob have hit " << bob.get_hit() << std::endl;
	std::cout << "Bob have energy " << bob.get_energy() << std::endl;
	bob.attack("YOU");
	bob.attack("YOU");
	bob.attack("YOU");
	bob.attack("YOU");
	bob.takeDamage(1);
	std::cout << "Bob have hit " << bob.get_hit() << std::endl;
	std::cout << "Bob have energy " << bob.get_energy() << std::endl;
	bob.beRepaired(1);
	bob.beRepaired(1);
	bob.beRepaired(1);
	bob.beRepaired(1);
	std::cout << "Bob have energy " << bob.get_energy() << std::endl;
	bob.takeDamage(15);
	bob.attack("YOU");
	bob.beRepaired(1);
	bob.takeDamage(15);
	std::cout << "Bob have hit " << bob.get_hit() << std::endl;
	std::cout << "Bob have energy " << bob.get_energy() << std::endl;
	return (0);
}