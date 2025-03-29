#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal
{
	public:
		Animal(void);
		Animal(std::string name);
		Animal(Animal const & src);
		Animal & operator=(Animal const & src);
		virtual ~Animal(void);
	
		virtual void makeSound(void) const;
		std::string getType(void) const;

	protected:
		std::string type;
};

#endif