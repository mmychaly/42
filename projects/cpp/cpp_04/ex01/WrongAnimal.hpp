#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal
{
	public:
		WrongAnimal(void);
		WrongAnimal(std::string name);
		WrongAnimal(WrongAnimal const & src);
		WrongAnimal & operator=(WrongAnimal const & src);
		virtual ~WrongAnimal(void);
	
		void makeSound(void) const;
		std::string getType(void) const;
	protected:
		std::string type;
};

#endif