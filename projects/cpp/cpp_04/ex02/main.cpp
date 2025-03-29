#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	int size = 10;
//	const AAnimal* t = new AAnimal();
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();
	delete j;
	delete i;

	std::cout << "\nNext test" << std::endl;
	AAnimal* AAnimals[size];
	for (int i = 0; i < size; i++)
	{
		if (i < size / 2)
			AAnimals[i] = new Dog();
		else
			AAnimals[i] = new Cat();
	}
	for (int i = 0; i < size; i++)
	{
		AAnimals[i]->makeSound();
	}
	for (int i = 0; i < size; i++)
	{
		delete AAnimals[i];
	}
	std::cout << "\nNext test" << std::endl;
	Cat x;
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
	return 0;
}