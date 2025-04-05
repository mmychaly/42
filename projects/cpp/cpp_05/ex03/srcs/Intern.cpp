#include "../includes/Intern.hpp"
#include "../includes/Form.hpp"
#include "../includes/Bureaucrat.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"

Intern::Intern(void)
{
	std::cout << "Intern default constructor called" << std::endl;
}
Intern::Intern(Intern const & src)
{
	std::cout << "Intern copy constructor called " << std::endl;
	(void)src;
}

Intern & Intern::operator=(Intern const & src)
{
	(void)src;
	return *this;
}

Intern::~Intern(void)
{
	std::cout << "Intern destructor called " << std::endl;
}

Form* Intern::createPresidentialPardonForm(std::string const target)
{
	Form *temp = new PresidentialPardonForm(target);
	return temp;
}
Form* Intern::createRobotomyRequestForm(std::string const target)
{
	Form *temp = new RobotomyRequestForm(target);
	return temp;
}

Form* Intern::createShrubberyCreationForm(std::string const target)
{
	Form *temp = new ShrubberyCreationForm(target);
	return temp;
}

const char* Intern::InvalidFormName::what() const throw()
{
	return ("Invalid form name");
}

Form* Intern::makeForm(std::string const name, std::string const target)
{
	std::string array[3] = { "presidential pardon", "robotomy request", "shrubbery creation"};
	Form* (Intern::*ptrs_func[3])(std::string const target) = {&Intern::createPresidentialPardonForm, &Intern::createRobotomyRequestForm, &Intern::createShrubberyCreationForm};
	Form* temp = NULL;

	for (int i = 0; i < 3; i++)
	{
		if (array[i] == name)
		{
			temp = (this->*ptrs_func[i])(target);
			std::cout << "Intern creates " << name << std::endl;
			return (temp);
		}
	}
	throw Intern::InvalidFormName();
}