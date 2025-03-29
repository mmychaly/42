#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include <string>
#include <iostream>

class Dog : public Animal
{
	public:
		Dog(void);
		Dog(Dog const & src);
		Dog & operator=(Dog const & src);
		~Dog(void);

		void makeSound(void) const;
};

#endif