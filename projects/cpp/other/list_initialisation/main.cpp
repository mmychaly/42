#include <iostream>
#include "Simple_class.hpp"

Simple::Simple(char a_1, int b_2) 
: a(a_1), b(b_2)
{
	std::cout << "Constructor called" << std::endl;
	std::cout << "a == " << this->a << std::endl;
	std::cout << "b == " << this->b << std::endl;
}

Simple::~Simple(void)
{
	std::cout << "Destructor called" << std::endl;
}

int main(void)
{
	Simple obj_1('a', 1);
	Simple obj_2('z', 100);

	return (0);
}