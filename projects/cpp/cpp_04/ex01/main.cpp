#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	int size = 10;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;
	delete i;

	std::cout << "\nNext test" << std::endl;
	Animal* animals[size];
	for (int i = 0; i < size; i++)
	{
		if (i < size / 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	for (int i = 0; i < size; i++)
	{
		animals[i]->makeSound();
	}
	for (int i = 0; i < size; i++)
	{
		delete animals[i];
	}
	std::cout << "\nNext test" << std::endl;
	Cat x;
	std::cout << x.getType();
	x.makeSound();
	x.getCatBrain()->set_idea("Meow");
	x.getCatBrain()->set_idea("Miauuuu");
	const std::string* allX = x.getCatBrain()->get_all_ideas();
	for (int i = 0; i < 100; i++)
	{
		if (allX[i].empty())
			break;
		std::cout << "Cat x : index == " << i << " Adresse == " << &allX[i] << " Idea : " << allX[i] << std::endl;
	}
	Cat y(x);
	const std::string* allY = y.getCatBrain()->get_all_ideas();
	for (int i = 0; i < 100; i++)
	{
		if (allY[i].empty())
			break;
		std::cout << "Cat y : index == " << i << " Adresse == " << &allY[i] << " Idea : " << allY[i] << std::endl;
	}
	Dog xx;
	std::cout << xx.getType();
	xx.makeSound();
	
	return 0;
}