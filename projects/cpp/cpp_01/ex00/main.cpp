#include "Zombie.hpp"

Zombie* newZombie( std::string name );
void randomChump( std::string name );

int main(void)
{
	Zombie* new_zomb = newZombie("NEWWWW");
	randomChump("Randoom");
	new_zomb->announce();
	delete new_zomb;
	return (0);
}