#include <iostream>

int main(void)
{
	int a = 5;
	int b = 10;

/*
//Конст перед типом == можно менять адрес сохраненный в указатели 
//	const int* ptr = &a
//	*ptr = 1;
	ptr = &b;
*/

//Конст перед менем указателя == можно менять значение сохраненный в указателе 
	int* const ptr = &a;  // Le pointeur lui-même est constant
//    *ptr = 7;   //  On peut modifier la valeur pointée
    ptr = &b; //  Erreur : Impossible de modifier l'adresse du pointeur
	std::cout << "ptr == " << *ptr << std::endl;
	return (0);
}