#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"
#include <string>
#include <iostream>

class Cat : public Animal
{
	public:
		Cat(void);
		Cat(Cat const & src);
		Cat & operator=(Cat const & src);
		~Cat(void);

		void makeSound(void) const;
		Brain* getCatBrain(void) const;
	private:
		Brain* cat_brain;
};

#endif