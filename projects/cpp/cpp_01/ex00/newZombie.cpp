#include "Zombie.hpp"

Zombie* newZombie( std::string name )
{
	Zombie* new_zomb = new Zombie(name);

	return (new_zomb);
}