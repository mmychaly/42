#include "../includes/MateriaSource.hpp"
#include <string>
#include <iostream>

MateriaSource::MateriaSource()
{
	std::cout << "MateriaSource default constructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		_source[i] = NULL;
	}
}
MateriaSource::MateriaSource(MateriaSource & src)
{
	std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		_source[i] = NULL;
	}
	*this = src; 
}
MateriaSource::~MateriaSource()
{
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4;  i++)
	{
		if (_source[i] != NULL)
		{
			delete _source[i];
			_source[i] = NULL;
		}
	}
}
MateriaSource & MateriaSource::operator=(MateriaSource & src)
{
	if (this != &src)
	{
		for (int i = 0; i < 4;  i++)
		{
			if (_source[i] != NULL)
			{
				delete _source[i];
				_source[i] = NULL;
			}
		}
		for (int i = 0; i < 4;  i++)
		{
			if (src._source[i] != NULL)
				_source[i] = src._source[i]->clone();
		}
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria* src)
{
	if (!src)
	{
		std::cout << "Materia doesn't exist!"  << std::endl;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		if (_source[i] == NULL )
		{
			_source[i] = src;
			std::cout << src->getType() << " : saved in source!" << " In index " << i << std::endl;
			return ;
		}
	}
	std::cout << "Source is full!"  << std::endl;
	delete src;
}
AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; i++)
	{
		if (_source[i] != NULL && (_source[i]->getType().compare(type)) == 0)
		{
			std::cout << "Materia " << type << " cloned!"<< std::endl;
			return (_source[i]->clone());
		}
	} 
	return (NULL);
}