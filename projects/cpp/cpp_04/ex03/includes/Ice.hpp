#ifndef ICE_HPP
#define ICE_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>
#include <iostream>

class Ice: public AMateria
{
	public:
		Ice(void);
		Ice(Ice const & src);
		~Ice(void);

		Ice & operator=(Ice const & src);

//		std::string const & getType() const;
		AMateria* clone(void) const;
		void use(ICharacter& target);
};

#endif