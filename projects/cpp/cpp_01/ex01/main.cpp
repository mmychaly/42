#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name );

int main(void)
{
	int nb_zombies = 5;
	int index_test_1 = 0;
	int index_test_2 = 4;
	std::string name_zomb = "def_zombie_name";
	if (nb_zombies < 2 || (index_test_1 < 0 || index_test_1 >= nb_zombies) || (index_test_2 < 0 || index_test_2 >= nb_zombies))
	{
		std::cerr << "Error in nb_zombies or one of the index_test" << std::endl;
		return (0);
	}

	Zombie* horde_zomb = zombieHorde(nb_zombies, name_zomb);

	std::cout << "Own tests" << std::endl;
	horde_zomb[index_test_1].announce();
	horde_zomb[index_test_1].set_name("ZOZO");
	horde_zomb[index_test_1].announce();
	horde_zomb[index_test_2].announce();
	horde_zomb[index_test_2].set_name("RORO");
	horde_zomb[index_test_2].announce();
	horde_zomb[index_test_1].set_name(name_zomb);
	horde_zomb[index_test_2].set_name(name_zomb);

	std::cout << "\nCall each one of the zombies" << std::endl;
	for (int i = 0; i < nb_zombies; i++)
	{
		horde_zomb[i].announce();
	}
	delete[] horde_zomb;
	return (0);
}