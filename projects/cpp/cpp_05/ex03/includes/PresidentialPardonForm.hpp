#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include <string>
#include <iostream>
#include "Form.hpp"

class Bureaucrat;

class PresidentialPardonForm: public Form
{
	public:
		PresidentialPardonForm(void);
		PresidentialPardonForm(const std::string target);
		PresidentialPardonForm(PresidentialPardonForm const & src);
		PresidentialPardonForm & operator=(PresidentialPardonForm const & src);
		~PresidentialPardonForm(void);
	
		std::string getTarget(void) const;
		void processExecuted(void) const;

		void execute(Bureaucrat const & executor) const;

	private:
		std::string _target;
};
#endif