#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

std::cout << j->getType() << " ";
j->makeSound();
std::cout << i->getType() << " ";
i->makeSound();
std::cout << meta->getType() << " ";
meta->makeSound();

std::cout << "\nWrong animal" << std::endl;
const WrongAnimal* wrongCat  = new WrongCat();
std::cout << wrongCat->getType() << " " ;
wrongCat->makeSound();

delete meta;
delete j;
delete i;
delete wrongCat;

return 0;
}