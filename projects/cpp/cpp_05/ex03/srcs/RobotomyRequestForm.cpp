#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/Form.hpp"
#include "../includes/Bureaucrat.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(void): Form("RobotomyRequestForm", 72, 45)
{
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string const target): Form("RobotomyRequestForm", 72, 45), _target(target)
{
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & src): Form("RobotomyRequestForm", 72, 45), _target(src.getTarget())
{
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}
RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & src)
{
	if (this != &src)
	{
		_target = src._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

std::string RobotomyRequestForm::getTarget(void) const
{
	return (_target);
}

void RobotomyRequestForm::processExecuted(void) const
{
	std::cout << "KZZZZZz... Bzzzz... Vrrrr..." << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << _target << " has been robotomized successfully!" <<std::endl;
	else
		std::cout << "The robotomy of " << _target << " is failed!" <<std::endl;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeOfRequired())
		throw Form::GradeTooLowException();
	if (!this->isSigned())
		throw Form::NotSignedForm();
	processExecuted();
}