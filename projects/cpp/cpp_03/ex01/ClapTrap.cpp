/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:17:20 by mmychaly          #+#    #+#             */
/*   Updated: 2025/03/19 02:17:21 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("defaul_name"), _hit(10), _energy(10), _attack(0)
{
	std::cout << "Defaul constructors of ClapTrap called" << std::endl;
	std::cerr << "Error: you forget make name of ClapTrap" << std::endl;
}
ClapTrap::ClapTrap(std::string str): _name(str), _hit(10), _energy(10), _attack(0) 
{
	std::cout << "Constructors of ClapTrap " << str << " called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const & src)
{
	std::cout << "Copy constructor of ClapTrap called" << std::endl;
	*this = src;
}

ClapTrap & ClapTrap::operator=(ClapTrap const & src)
{
	if (this != &src)
	{
		_name = src.get_name();
		_hit = src.get_hit();
		_energy = src.get_energy();
		_attack = src.get_attack();
	}
	return *this;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "Destructors of ClapTrap " << this->get_name() << " called" << std::endl;
}

std::string ClapTrap::get_name(void) const
{
	return this->_name;
}

int ClapTrap::get_hit(void) const
{
	return this->_hit;
}

int ClapTrap::get_energy(void) const
{
	return this->_energy;
}

int ClapTrap::get_attack(void) const
{
	return this->_attack;
}

void ClapTrap::set_add_hit(unsigned int hit_points)
{
	if (hit_points > INT_MAX - (unsigned int)this->_hit)
		this->_hit = INT_MAX;
	else
		this->_hit = this->_hit + hit_points;
}

void ClapTrap::set_left_hit(unsigned int hit_points)
{
	if (hit_points > INT_MAX)
		hit_points = INT_MAX;
	if (hit_points > (unsigned int)this->_hit)
		this->_hit = 0;
	else
		this->_hit = this->_hit - hit_points;
}

void ClapTrap::set_energy(void)
{
	this->_energy--;
	if (this->_energy < 0)
		this->_energy = 0;
}

void ClapTrap::attack(const std::string& target)
{
	if (this->get_energy() <= 0)
	{
		std::cout << "ClapTrap " << this->get_name() << " dont have energy for attack !" << std::endl;
		return;
	}
	if (this->get_hit() <= 0)
	{
		std::cout << "ClapTrap " << this->get_name() << " dont have hit for attack !" << std::endl;
		return;
	}
	std::cout << "ClapTrap " << this->get_name() << " attacks " << target << ", causing " << this->get_attack() << " points of damage!" << std::endl;
	this->set_energy();

}
void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->get_hit() <= 0)
	{
		std::cout << "ClapTrap " << this->get_name() << " dont have hit for take dommage !" << std::endl;
		return;
	}
	std::cout << "ClapTrap " << this->get_name() << " take " << amount << " points of damage!" << std::endl;
	this->set_left_hit(amount);
	
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->get_energy() <= 0)
	{
		std::cout << "ClapTrap " << this->get_name() << " dont have energy for be repaired !" << std::endl;
		return;
	}
	if (this->get_hit() <= 0)
	{
		std::cout << "ClapTrap " << this->get_name() << " dont have hit for be repaired!" << std::endl;
		return;
	}
	std::cout << "ClapTrap " << this->get_name() << " regains " << amount << " hit points !" << std::endl;
	this->set_add_hit(amount);
	this->set_energy();
}