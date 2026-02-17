#include <iostream>
#include "Simple_class.hpp"


Simple::Simple(int nbr)
{

	std::cout << "Constructor called" << std::endl;
	std::cout << "Obk nbr == " << nbr << std::endl;
	this->nb = 42;
	this->new_func();
}

Simple::~Simple(void)
{
	std::cout << "Destructor called" << std::endl;
}

void Simple::new_func(void)
{
	std::cout << "in new_func" << std::endl;
	std::cout << "nb == " << this->nb << std::endl;
}

int main(void)
{
	Simple obj(1);
	Simple obj_2(2);
	std::cout << "in main" << std::endl;
	return (0);
}