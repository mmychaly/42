#include "../includes/Bureaucrat.hpp"
#include "../includes/AForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"

int main(void)
{

	Bureaucrat *bob = NULL;
	std::cout << "Test shrubbery" << std::endl;
	AForm *shrubbery = new ShrubberyCreationForm("Home");
	try
	{
		bob = new Bureaucrat("bob",100);
		std::cout << *bob << std::endl;
		std::cout << *shrubbery << std::endl;
		bob->signForm(*shrubbery);
		std::cout << *shrubbery << std::endl;
		bob->executeForm(*shrubbery);
		delete bob;
		delete shrubbery;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	if (bob == NULL)
	{
		delete shrubbery;
	}
	
	std::cout << "\nTest robotomy" << std::endl;
	AForm *robotomy = new RobotomyRequestForm("Bender");
	try
	{
		bob = new Bureaucrat("bob",20);
		std::cout << *bob << std::endl;
		std::cout << *robotomy << std::endl;
		bob->signForm(*robotomy);
		std::cout << *robotomy << std::endl;
		bob->executeForm(*robotomy);
		bob->executeForm(*robotomy);
		delete bob;
		delete robotomy;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	if (bob == NULL)
	{
		delete robotomy;
	}

	std::cout << "\nTest Presidential" << std::endl;
	AForm *presidential = new PresidentialPardonForm ("John");
	try
	{
		bob = new Bureaucrat("bob",5);
		std::cout << *bob << std::endl;
		std::cout << *presidential << std::endl;
		bob->signForm(*presidential);
		std::cout << *presidential << std::endl;
		bob->executeForm(*presidential);
		delete bob;
		delete presidential;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	if (bob == NULL)
	{
		delete presidential;
	}


	std::cout << "\nTest copy" << std::endl;
	PresidentialPardonForm *original = new PresidentialPardonForm ("Mike");
	PresidentialPardonForm *copy = new PresidentialPardonForm (*original);
	std::cout << *original;
	std::cout << original->getTarget() << std::endl;
	std::cout << *copy;
	std::cout << copy->getTarget() << std::endl;
	copy->processExecuted();
	delete original;
	delete copy;
	return 0; 
}
