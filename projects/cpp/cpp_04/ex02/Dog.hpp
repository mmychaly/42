#ifndef DOG_HPP
#define DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"
#include <string>
#include <iostream>

class Dog : public AAnimal
{
	public:
		Dog(void);
		Dog(Dog const & src);
		Dog & operator=(Dog const & src);
		~Dog(void);

		void makeSound(void) const;
		Brain* getDogBrain(void) const;

	private:
		Brain* dog_brain;
};

#endif