/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:16:58 by mmychaly          #+#    #+#             */
/*   Updated: 2025/03/19 03:56:46 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void):ClapTrap()
{
	std::cout << "Defaul constructors of ScavTrap called" << std::endl;
	std::cerr << "Error: you forget make name of ScavTrap" << std::endl;
	this->_attack = 20;
	this->_energy = 50;
	this->_hit = 100;
}

ScavTrap::ScavTrap(std::string str): ClapTrap(str)
{
	std::cout << "Constructors of ScavTrap " << str << " called" << std::endl;
	this->_attack = 20;
	this->_energy = 50;
	this->_hit = 100;
}

ScavTrap::ScavTrap(ScavTrap const & src): ClapTrap(src.get_name())
{
	std::cout << "Copy constructor of ScavTrap " << src.get_name() << " called" << std::endl;
	*this = src;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "Destructors of ScavTrap " << this->get_name() << " called" << std::endl;
}

ScavTrap & ScavTrap::operator=(ScavTrap const & src)
{
	if (this != &src)
	{
		this->_name = src.get_name();
		this->_attack = src.get_attack();
		this->_energy = src.get_energy();
		this->_hit = src.get_hit();
	}
	return *this;
}

void ScavTrap::attack(const std::string& target)
{
	if (this->get_energy() <= 0)
	{
		std::cout << "ScavTrap " << this->get_name() << " dont have energy for attack !" << std::endl;
		return;
	}
	if (this->get_hit() <= 0)
	{
		std::cout << "ScavTrap " << this->get_name() << " dont have hit for attack !" << std::endl;
		return;
	}
	std::cout << "ScavTrap " << this->get_name() << " attacks " << target << ", causing " << this->get_attack() << " points of damage!" << std::endl;
	this->set_energy();
}

void ScavTrap::guardGate(void)
{
	if (this->get_energy() <= 0)
	{
		std::cout << "ScavTrap " << this->get_name() << " dont have energy for gate keeper mode !" << std::endl;
		return;
	}
	if (this->get_hit() <= 0)
	{
		std::cout << "ScavTrap " << this->get_name() << " dont have hit for gate keeper mode !" << std::endl;
		return;
	}
	std::cout << "ScavTrap " << this->get_name() << " gate keeper mode" << std::endl;
}