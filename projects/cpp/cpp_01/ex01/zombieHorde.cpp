#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie* hordezomb = new Zombie[N];
	
	for (int i = 0; i < N; i++)
	{
		hordezomb[i].set_name(name);
	}
	return hordezomb;
}