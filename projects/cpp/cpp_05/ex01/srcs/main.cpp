#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"

int main(void)
{

	Bureaucrat *bob = NULL;
	Form *a = NULL;
	try
	{
		bob = new Bureaucrat("bob",10);
		a = new Form("a", 9, 150);
		bob->signForm(*a);
		std::cout << *bob << std::endl;
		std::cout << *a << std::endl;
		bob->incrementGrade();
		bob->signForm(*a);
		std::cout << *bob << std::endl;
		std::cout << *a << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	if (bob == NULL || a == NULL)
	{
		delete bob;
		delete a;
		return 0;
	}
	
	std::cout << "Test copy" << std::endl;
	try
	{
		Bureaucrat joj(*bob);
		Form x(*a);
		delete bob;
		delete a;
		std::cout << joj << std::endl;
		std::cout << x << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0; 
}
