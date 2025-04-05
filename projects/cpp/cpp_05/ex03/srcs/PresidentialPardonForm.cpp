#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/Form.hpp"
#include "../includes/Bureaucrat.hpp"


PresidentialPardonForm::PresidentialPardonForm(void): Form("PresidentialPardonForm", 25, 5)
{
	std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string const target): Form("PresidentialPardonForm", 25, 5), _target(target)
{
	std::cout << "PresidentialPardonForm constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & src): Form("PresidentialPardonForm", 25, 5), _target(src.getTarget())
{
	std::cout << "PresidentialPardonForm copy constructor called " << std::endl;
}
PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & src)
{
	if (this != &src)
	{
		_target = src._target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	std::cout << "PresidentialPardonForm destructor called " << std::endl;
}

std::string PresidentialPardonForm::getTarget(void) const
{
	return (_target);
}

void PresidentialPardonForm::processExecuted(void) const
{
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeOfRequired())
		throw Form::GradeTooLowException();
	if (!this->isSigned())
		throw Form::NotSignedForm();
	processExecuted();
}