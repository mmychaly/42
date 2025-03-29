#ifndef CURE_HPP
#define CURE_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>
#include <iostream>

class Cure: public AMateria
{
	public:
		Cure(void);
		Cure(Cure const & src);
		~Cure(void);

		Cure & operator=(Cure const & src);

//		std::string const & getType() const;
		AMateria* clone(void) const;
		void use(ICharacter& target);
};

#endif