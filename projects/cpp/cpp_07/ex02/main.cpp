#include "Array.hpp"


int main(void)
{
	std::cout << "Test int array" << std::endl;
	try
	{
		Array<int> a(5);
        for (unsigned int i = 0; i < a.size(); i++)
		{
            a[i] = i * 5;
        }
        for (unsigned int i = 0; i < a.size(); i++)
		{
            std::cout << "a[" << i << "] == " << a[i] << std::endl;
        }
		std::cout << a[10] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;;
	}
	
	std::cout << "Test string array" << std::endl;
	Array<std::string>* b = NULL;
	try
	{
		b  = new Array<std::string>(3);
		(*b)[0] = "He, ";
		(*b)[1] = "it's ";
		(*b)[2] = "okay?";
		for (unsigned int i = 0; i < b->size(); i++)
		{
            std::cout << "b[" << i << "] == " << (*b)[i] << std::endl;
        }
		std::cout << (*b)[4] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Test copy" << std::endl;
	Array<std::string> x(*b);
	(*b)[0] = "New string";

	std::cout << "x[0] = " << x[0] << std::endl;
    std::cout << "b[0] = " << (*b)[0] << std::endl;
	delete b;
	return 0;
}