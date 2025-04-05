#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/Intern.hpp"

int main(void)
{
	Intern someRandomIntern;
	Form* rrf = NULL;
	std::cout << "\nTest RobotomyRequestForm\n" << std::endl;
	try 
	{
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	}
	catch(const std::exception&  e)
	{
		std::cout << "Intern could not create the form: " << e.what() << std::endl;
	}
	if (rrf)
	{
		std::cout << std::endl;
		std::cout << *rrf;
		std::cout << "Target is " << rrf->getTarget() << std::endl;
		rrf->processExecuted();
		rrf->processExecuted();
		delete rrf;
	}
	rrf = NULL;

	std::cout << "\nTest PresidentialPardonForm\n" << std::endl;
	try 
	{
		rrf = someRandomIntern.makeForm("presidential pardon", "Daniel");
	}
	catch(const std::exception&  e)
	{
		std::cout << "Intern could not create the form: " << e.what() << std::endl;
	}
	if (rrf)
	{
		std::cout << std::endl;
		std::cout << *rrf;
		std::cout << "Target is " << rrf->getTarget() << std::endl;
		rrf->processExecuted();
		delete rrf;
	}
	rrf = NULL;

	std::cout << "\nTest ShrubberyCreationForm\n" << std::endl;
	try 
	{
		rrf = someRandomIntern.makeForm("shrubbery creation", "Garden");
	}
	catch(const std::exception&  e)
	{
		std::cout << "Intern could not create the form: " << e.what() << std::endl;
	}
	if (rrf)
	{
		std::cout << std::endl;
		std::cout << *rrf;
		std::cout << "Target is " << rrf->getTarget() << std::endl;
		rrf->processExecuted();
		delete rrf;
	}
	rrf = NULL;

	std::cout << "\nTest Invalide form\n" << std::endl;
	try 
	{
		rrf = someRandomIntern.makeForm("invalide form", "uru");
	}
	catch(const std::exception&  e)
	{
		std::cout << "Intern could not create the form: " << e.what() << std::endl;
	}
	if (rrf)
	{
		std::cout << std::endl;
		std::cout << *rrf;
		std::cout << "Target is " << rrf->getTarget() << std::endl;
		rrf->processExecuted();
		delete rrf;
	}

	return 0; 
}
