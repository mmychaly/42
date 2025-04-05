#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <string>
#include <iostream>
#include "Form.hpp"

class Bureaucrat;

class RobotomyRequestForm: public Form
{
	public:
		RobotomyRequestForm(void);
		RobotomyRequestForm(const std::string target);
		RobotomyRequestForm(RobotomyRequestForm const & src);
		RobotomyRequestForm & operator=(RobotomyRequestForm const & src);
		~RobotomyRequestForm(void);
	
		std::string getTarget(void) const;
		void processExecuted(void) const;

		void execute(Bureaucrat const & executor) const;

	private:
		std::string _target;
};
#endif