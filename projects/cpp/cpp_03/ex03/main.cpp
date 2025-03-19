/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:17:26 by mmychaly          #+#    #+#             */
/*   Updated: 2025/03/19 05:21:54 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main(void)
{
	DiamondTrap mike("Mika");
	mike.whoAmI();
	std::cout << "\nMika have hit " << mike.get_hit() << std::endl;
	std::cout << "Mika have energy " << mike.get_energy() << std::endl;
	mike.attack("bob");
	mike.takeDamage(20);
	mike.beRepaired(10);
	std::cout << "\nMika have hit " << mike.get_hit() << std::endl;
	std::cout << "Mika have energy " << mike.get_energy() << std::endl;
	return (0);
}