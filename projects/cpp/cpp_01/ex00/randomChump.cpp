#include "Zombie.hpp"

void randomChump( std::string name )
{
	Zombie rand_zomb(name);

	rand_zomb.announce();
}