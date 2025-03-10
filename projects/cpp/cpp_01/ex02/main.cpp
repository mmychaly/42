#include <iostream>
#include <string>

int main(void)
{
	std::string str = "HI THIS IS BRAIN";
	std::string* stringPTR = &str;
	std::string& stringREF = str;

	std::cout << "Memory addresses:"<< std::endl;
	std::cout << "Address of the string variable is " << &str << std::endl;
	std::cout << "Address held by stringPTR is " << stringPTR << std::endl;
	std::cout << "Address held by stringREF is " << &stringREF << std::endl;

	std::cout << "\nValues:" << std::endl;
	std::cout << "Value of the string variable is " << str << std::endl;
	std::cout << "Value pointed to by stringPTR is " << *stringPTR << std::endl;
	std::cout << "Value pointed to by stringREF is " << stringREF << std::endl;

	return (0);
}