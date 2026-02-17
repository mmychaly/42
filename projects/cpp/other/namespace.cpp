#include <stdio.h>
#include <iostream>

int g_var = 1;
int f(void){return 2;}

namespace first 
{
	int g_var = 5;
	int f(void){return 10;}
}

namespace seconde 
{
	int g_var = 100;
	int f(void){return 101;}
	void print()
	{
		printf("print in seconde : %d\n", f());
	}
	
}

namespace copy = first;

int main(void)
{
	char buffer[50];
	printf("out\ng_var: %d\n", ::g_var);
	printf("f(): %d\n", ::f());

	printf("first g_var: %d\n", first::g_var);
	printf("first f(): %d\n", first::f());

	printf("seconde g_var: %d\n", seconde::g_var);
	printf("seconde f(): %d\n", seconde::f());

	printf("copy g_var: %d\n", copy::g_var);
	printf("copy f(): %d\n", copy::f());

	std::cout << "cout : g_var == " << seconde::g_var << " f() == " << seconde::f() << std::endl; //либо << "\n";
	seconde::print();
	std::cin >> buffer;
	std::cout << std::endl;
	std::cout << "in\nstd::cin == " << buffer << std::endl;
}