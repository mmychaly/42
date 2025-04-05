#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/AForm.hpp"
#include "../includes/Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(void): AForm("ShrubberyCreationForm", 145, 137)
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const target): AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & src): AForm("ShrubberyCreationForm", 145, 137), _target(src.getTarget())
{
	std::cout << "ShrubberyCreationForm copy constructor called " << std::endl;
}
ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & src)
{
	if (this != &src)
	{
		this->_target = src.getTarget();
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << "ShrubberyCreationForm destructor called " << std::endl;
}

std::string ShrubberyCreationForm::getTarget(void) const
{
	return (_target);
}

void ShrubberyCreationForm::processExecuted(void) const
{
	std::string fileName = _target + "_shrubbery";
	std::ofstream file(fileName.c_str());
	if (file)
	{
		file << "   ccee88oo\n"
           		" C8O8O8Q8PoOb o8oo\n"
          		"dOB69QO8PdUOpugoO9bD\n"
           		"CgggbU8OU qOp qOdoUOdcb\n"
        		"    6OuU  /p u gcoUodpP\n"
           		"      \\\\//  /douUP\n"
           		"        \\\\////\n"
           		"         |||/\\\n"
           		"         |||\\/\n"
           		"         |||||\n"
          		"   .....//||||\\....\n";
	}
	file.close();
	std::cout << "Shrubbery planted in " << _target << "_shrubbery." << std::endl;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeOfRequired())
		throw AForm::GradeTooLowException();
	if (!this->isSigned())
		throw AForm::NotSignedForm();
	processExecuted();
}
