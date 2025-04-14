#include "ScalarConverter.hpp"
#include <limits>
#include <string>
#include <cstdlib>
#include <cerrno>
#include <iomanip>

void error()
{
	std::cout << "char: impossible"<< std::endl;
	std::cout << "int: impossible"<< std::endl;
	std::cout << "float: impossible"<< std::endl;
	std::cout << "double: impossible"<< std::endl;
}

bool checkPseudoLiterals(const std::string& literal)
{
	if (literal == "nan" || literal == "nanf")
		return true;
	else if (literal == "+inf" || literal == "+inff")
		return true;
	else if (literal == "-inf" || literal == "-inff")
		return true;
	return false;
}

bool checkFloat(const std::string& literal)
{
	int flag_point = 0;
	if (literal.length() > 1 && literal[literal.length() - 1] == 'f')
	{
		for (size_t i = 0; i < (literal.length() - 1); i++ )
		{
			if ( i == 0 && (literal[i] == '-' || literal[i] == '+' ))
			{
				continue;
			}
			if (!isdigit(literal[i]) && literal[i] == '.' && flag_point == 0)
			{
				flag_point++;
				continue;
			}
			if (!isdigit(literal[i]))
				return false;
		}
		return true;
	}
	return false;
}

bool checkDouble(const std::string& literal)
{
	int flag_point = 0;
	if (literal.find('.') != std::string::npos)
	{
		for (size_t i = 0; i < literal.length(); i++ )
		{
			if ( i == 0 && (literal[i] == '-' || literal[i] == '+' ))
			{
				continue;
			}
			if (!isdigit(literal[i]) && literal[i] == '.' && flag_point == 0)
			{
				flag_point++;
				continue;
			}
			if (!isdigit(literal[i]))
				return false;
		}
		return true;
	}
	return false;
}

bool checkInt(const std::string& literal)
{
		for (size_t i = 0; i < literal.length(); i++ )
		{
			if ( i == 0 && (literal[i] == '-' || literal[i] == '+' ))
			{
				continue;
			}
			if (!isdigit(literal[i]))
				return false;
		}
		return true;
}

void getPseudoLiterals(const std::string& literal)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (literal == "nan" || literal == "nanf")
	{
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (literal == "+inf" || literal == "+inff")
	{
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if (literal == "-inf" || literal == "-inff")
	{
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}

void getCharConvert(const std::string& literal)
{
	std::cout << "char: " << "'" << literal[0] << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(literal[0]) << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(literal[0]) << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(literal[0]) << std::endl;
}

void getnbr(const std::string& literal)
{
	char* end;
    errno = 0;
	double nb = std::strtod(literal.c_str(), &end);
	if (errno == ERANGE || end == literal.c_str()) 
	{
        error();
        return ;
    }
    if (nb > std::numeric_limits<float>::max() || nb < -std::numeric_limits<float>::max())
	{
		std::cout << "char: impossible"<< std::endl;
		std::cout << "int: impossible"<< std::endl;
		std::cout << "float: impossible"<< std::endl;
		std::cout << "double: " << nb << std::endl;
    }
	else if (nb > std::numeric_limits<int>::max() || nb < std::numeric_limits<int>::min())
	{
		std::cout << "char: impossible"<< std::endl;
		std::cout << "int: impossible"<< std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(nb) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << nb << std::endl;
	}
	else
	{
		if (static_cast<int>(nb) < 0 || static_cast<int>(nb) > 127)
		{
			std::cout << "char: impossible" << std::endl;
		}
		else if (static_cast<int>(nb) < 32 || static_cast<int>(nb) == 127)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: " << "'" << static_cast<char>(nb) << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(nb) << std::endl;
		std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(nb) << "f" << std::endl;
		std::cout << "double: " << std::fixed << std::setprecision(1) << nb << std::endl;
	}
}


void ScalarConverter::convert(const std::string& literal)
{
	if (checkPseudoLiterals(literal) == true)
		getPseudoLiterals(literal);
	else if (checkFloat(literal))
		getnbr(literal);
	else if (checkDouble(literal))
		getnbr(literal);
	else if (checkInt(literal))
		getnbr(literal);
	else if (literal.length() == 1 && isprint(literal[0]))
		getCharConvert(literal);
	else
		error();
}
