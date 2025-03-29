#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"
#include <string>
#include <iostream>

class MateriaSource: public IMateriaSource
{
	public:
		MateriaSource();
		MateriaSource(MateriaSource & src);
		~MateriaSource();
		MateriaSource & operator=(MateriaSource & src);

		void learnMateria(AMateria* src);
		AMateria* createMateria(std::string const & type);
	private:
		AMateria* _source[4];
};

#endif