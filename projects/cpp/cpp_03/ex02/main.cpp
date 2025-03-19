/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:17:26 by mmychaly          #+#    #+#             */
/*   Updated: 2025/03/19 03:58:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
	FragTrap bob("bob");
	FragTrap bob_2(bob);
	std::cout << std::endl;
	bob.highFivesGuys();
	std::cout << "bob have hit " << bob.get_hit() << std::endl;
	std::cout << "bob have energy " << bob.get_energy() << std::endl;
	bob.attack("YOU");
	bob.takeDamage(3);
	bob.beRepaired(1);
	bob.beRepaired(1);
	bob.attack("YOU");
	bob.takeDamage(1);
	bob.beRepaired(1);
	bob.beRepaired(1);
	std::cout << "bob have hit " << bob.get_hit() << std::endl;
	std::cout << "bob have energy " << bob.get_energy() << std::endl;
	bob.takeDamage(200);
	bob.attack("YOU");
	bob.beRepaired(1);
	bob.takeDamage(15);
	std::cout << "bob have hit " << bob.get_hit() << std::endl;
	std::cout << "bob have energy " << bob.get_energy() << std::endl;
	std::cout << "\nbob_2 have hit " << bob_2.get_hit() << std::endl;
	std::cout << "bob_2 have energy " << bob_2.get_energy() << std::endl;
	
	for (int i = 0; i < 110; i++)
	{
		if (bob_2.get_energy() == 0)
			break;
		bob_2.attack("YOU");
	}
	bob_2.attack("YOU");
	std::cout << "\nbob_2 have hit " << bob_2.get_hit() << std::endl;
	std::cout << "bob_2 have energy " << bob_2.get_energy() << std::endl;
	bob_2.highFivesGuys();
	std::cout << std::endl;
	return (0);
}