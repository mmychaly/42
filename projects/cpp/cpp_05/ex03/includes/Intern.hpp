#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <iostream>
#include "Form.hpp"


class Intern
{
	public:
		Intern(void);
		Intern(Intern const & src);
		Intern & operator=(Intern const & src);
		~Intern(void);

		Form* makeForm(std::string const name, std::string const target);
		
		Form* createPresidentialPardonForm(std::string const target);
		Form* createRobotomyRequestForm(std::string const target);
		Form* createShrubberyCreationForm(std::string const target);

		class InvalidFormName: public std::exception
		{
			public:
			virtual const char* what() const throw();
		};
};

#endif