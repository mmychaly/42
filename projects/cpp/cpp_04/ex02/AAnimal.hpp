#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>
#include <iostream>

class AAnimal
{
	public:
		AAnimal(void);
		AAnimal(std::string name);
		AAnimal(AAnimal const & src);
		AAnimal & operator=(AAnimal const & src);
		virtual ~AAnimal(void);
	
		virtual void makeSound(void) const = 0;
		std::string getType(void) const;

	protected:
		std::string type;
};

#endif