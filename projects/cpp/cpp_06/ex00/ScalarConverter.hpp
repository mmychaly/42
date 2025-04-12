#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>

class ScalarConverter 
{
	public:
    	static void convert(const std::string& literal);

	private:
    	ScalarConverter();
    	ScalarConverter(const ScalarConverter&);
    	ScalarConverter& operator=(const ScalarConverter&);
    	~ScalarConverter();
};

#endif