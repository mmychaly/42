#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <string>
#include <iostream>

class Character: public ICharacter
{
	public:
		Character(void);
		Character(std::string const & type);
		Character(Character const & src);
		~Character(void);
		Character & operator=(Character const & src);

		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);

		void save_unequippedItems(AMateria* src);
		int len_unequippedItems(void) const;
		void delete_unequippedItems(void);
	private:
		std::string _name;
		AMateria* _inventory[4];
		AMateria** _unequippedItems;
};

#endif