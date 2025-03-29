#include "../includes/ICharacter.hpp"
#include "../includes/AMateria.hpp"
#include "../includes/IMateriaSource.hpp"
#include "../includes/MateriaSource.hpp"
#include "../includes/Character.hpp"
#include "../includes/Cure.hpp"
#include "../includes/Ice.hpp"

int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;

	std::cout << "\nMy tests" << std::endl;

	ICharacter* mike = new Character("mike");
	IMateriaSource* newSrc = new MateriaSource();
	AMateria* newTmp = new Ice();
	newSrc->learnMateria(newTmp);
	for (int i = 0; i < 4 ; i++)
	{
		newTmp = new Cure();
		newSrc->learnMateria(newTmp);
	}
	for (int i = 0; i < 6 ; i++)
	{
		mike->equip(newSrc->createMateria("cure"));
	}
	mike->unequip(10);
	mike->unequip(3);
	mike->equip(newSrc->createMateria("stone"));
	mike->equip(newSrc->createMateria("ice"));
	for (int i = 0; i < 6 ; i++)
	{
		mike->use(i, *mike);
	}
	mike->unequip(2);
	mike->unequip(0);
	delete mike;
	delete newSrc;
return 0;
}