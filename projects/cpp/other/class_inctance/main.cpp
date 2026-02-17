#include <iostream>
#include "Simple_class.hpp"


Simple::Simple(void)
{
	std::cout << "Constructor called" << std::endl;
}

Simple::~Simple(void)
{
	std::cout << "Destructor called" << std::endl;
}

void Simple::new_func(void)
{
	std::cout << "new_func" << std::endl;
}

int main(void)
{
	Simple obj;
	std::cout << "in main" << std::endl;
	obj.nb = 42;
	std::cout << "obj.nb == " << obj.nb << std::endl;
	obj.new_func();
	return (0);
}