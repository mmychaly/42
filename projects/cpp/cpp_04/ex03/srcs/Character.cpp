#include "../includes/Character.hpp"
#include "../includes/AMateria.hpp"
#include <string>
#include <iostream>


Character::Character(void): _name("default")
{
	std::cout << "Character default constructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		_inventory[i] = NULL;
	}
	_unequippedItems = NULL;
}

Character::Character(std::string const & type): _name(type)
{
	std::cout << "Character " << type << " constructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		_inventory[i] = NULL;
	}
	_unequippedItems = NULL;
}

Character::Character(Character const & src)
{
	std::cout << "Character copy constructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		_inventory[i] = NULL;
	}
	_unequippedItems = NULL;
	*this = src; 
}


Character::~Character(void)
{
	std::cout << "Character destructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		if (_inventory[i] != NULL)
		{
			delete _inventory[i];
			_inventory[i] = NULL;
		}
	}
	this->delete_unequippedItems();
}

Character & Character::operator=(Character const & src)
{
	if (this != &src)
	{
		for (int i = 0; i < 4;  i++)
		{
			if (_inventory[i] != NULL)
			{
				delete _inventory[i];
				_inventory[i] = NULL;
			}
		}
		this->delete_unequippedItems();
		this->_name = src._name;
		for (int i = 0; i < 4;  i++)
		{
			if (src._inventory[i] != NULL)
				_inventory[i] = src._inventory[i]->clone();
		}
		if (src._unequippedItems != NULL )
		{
			int len = (int)src.len_unequippedItems();
			this->_unequippedItems = new AMateria*[len + 1 ];
			for (int i = 0; i < len; i++)
			{
				this->_unequippedItems[i] = src._unequippedItems[i]->clone();
			}
			this->_unequippedItems[len + 1] = NULL;
		}
	}
	return *this;
}


std::string const & Character::getName() const
{
	return _name;
}

void Character::equip(AMateria* m)
{
	if (!m)
	{
		std::cout << "Materia doesn't exist!"  << std::endl;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i] == NULL )
		{
			_inventory[i] = m;
			std::cout << m->getType() << " : equiped to inventory!" << " In index " << i << std::endl;
			return ;
		}
	}
	std::cout << "Inventory is full!"  << std::endl;
	delete m;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4)
	{
		std::cout << "Wrong index"  << std::endl;
		return;
	}
	if (_inventory[idx] == NULL)
	{
		std::cout << "Invetory in index " << idx << " is empty" << std::endl;
		return ;
	}
	else 
	{
		std::cout << _inventory[idx]->getType() << " in index " << idx << " in invetory is succesfully unequip" << std::endl;
		save_unequippedItems(_inventory[idx]);
		_inventory[idx] = NULL;
		return ;
	}
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= 4)
	{
		std::cout << "Wrong index"  << std::endl;
		return;
	}
	if (_inventory[idx] == NULL)
	{
		std::cout << "Invetory in index " << idx << "is empty" << std::endl;
		return ;
	}
	else
		_inventory[idx]->use(target);
}

void Character::save_unequippedItems(AMateria* src)
{
	if (_unequippedItems == NULL)
	{
		this->_unequippedItems = new AMateria*[2];
		_unequippedItems[0] = src;
		_unequippedItems[1] = NULL;
	}
	else
	{
		int len  = this->len_unequippedItems();
		AMateria** temp = new AMateria*[len + 2];
		temp[len + 1] = NULL;
		for (int i = 0; i < len; i++)
		{
			temp[i] = _unequippedItems[i]->clone();
		}
		temp[len ] = src;
		delete_unequippedItems();
		this->_unequippedItems = temp;
	}
	std::cout << "Save unequipped material " << src->getType() << std::endl;
	std::cout << "_unequippedItems" << std::endl;
	for (int i = 0; i < len_unequippedItems(); i++)
	{
		std::cout << i <<" == " << _unequippedItems[i]->getType() << std::endl;
	}
}

int Character::len_unequippedItems(void) const
{
	int i = 0;

	if (_unequippedItems != NULL)
	{
		while (_unequippedItems[i] != NULL)
		{
			i++;
		}
	}
	return i;
}

void Character::delete_unequippedItems(void)
{
	int i = 0;

	if (this->_unequippedItems != NULL)
	{
		while (_unequippedItems[i] != NULL)
		{
			delete _unequippedItems[i];
			i++;
		}
		delete[] _unequippedItems;
		_unequippedItems = NULL;
	}
}