/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:18:24 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/14 01:46:49 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime> 

Base * generate(void)
{
	
	int rnd = std::rand() % 3;
	switch(rnd)
	{
		case 0:
			std::cout << "An object of type A is created." << std::endl;
			return (new A());
		case 1:
			std::cout << "An object of type B is created." << std::endl;
			return (new B());
		case 2:
			std::cout << "An object of type C is created." << std::endl;
			return (new C());
		default:
			std::cout << "Unexpected error in random generation." << std::endl;
			return NULL;
	}
}

void identify(Base* p)
{
	A* temp_a = dynamic_cast<A*>(p);
	if (temp_a != NULL)
	{
		std::cout << "Type of the object pointed to by p is A" << std::endl;
		return; 
	}
	B* temp_b = dynamic_cast<B*>(p);
	if (temp_b != NULL)
	{
		std::cout << "Type of the object pointed to by p is B" << std::endl;
		return; 
	}
	C* temp_c = dynamic_cast<C*>(p);
	if (temp_c != NULL)
	{
		std::cout << "Type of the object pointed to by p is C" << std::endl;
		return; 
	}
}
void identify(Base& p)
{
	try
	{
		A& tempA= dynamic_cast<A&>(p);
		(void) tempA;
		std::cout << "Type of the object referenced by p is A" << std::endl;
		return ;
	}
	catch(const std::exception & a)
	{
	}

	try
	{
		B& tempB= dynamic_cast<B&>(p);
		(void) tempB;
		std::cout << "Type of the object referenced by p is B" << std::endl;
		return ;
	}
	catch(const std::exception & b)
	{
	}

	try
	{
		C& tempC= dynamic_cast<C&>(p);
		(void) tempC;
		std::cout << "Type of the object referenced by p is C" << std::endl;
		return ;
	}
	catch(const std::exception & c)
	{
	}
	
}

int main(void)
{
	std::srand(std::time(0));
	
	Base* temp = generate();
	identify(temp);
	identify(*temp);

	delete temp;
	return (0);
}