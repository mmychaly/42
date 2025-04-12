#include "ScalarConverter.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong number of arguments!" << std::endl;
		return (1);
	}
	else 
		ScalarConverter::convert(argv[1]);
	return (0);
}