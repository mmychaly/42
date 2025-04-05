#include "Bureaucrat.hpp"

int main(void)
{
	std::cout << "\nTest: Grade Too High " << std::endl;
	try
	{
		Bureaucrat bob("bob", 3);
		std::cout << bob << std::endl;
		bob.decrementGrade();
		std::cout << bob << std::endl;
		bob.incrementGrade();
		bob.incrementGrade();
		bob.incrementGrade();
		std::cout << bob << std::endl;
		bob.incrementGrade();
		std::cout << bob << std::endl;
	}
	catch(Bureaucrat::GradeTooHighException& e)
	{
		std::cerr << "bob " << " : " << e.what() << std::endl;
	}
	catch(Bureaucrat::GradeTooLowException& e)
	{
		std::cerr << "bob " << " : " << e.what() << std::endl;
	}
	


	std::cout << "\nNext test: Grade Too Low " << std::endl;
	try
	{
		Bureaucrat pop("pop", 145);
		std::cout << pop << std::endl;
		pop.incrementGrade();
		std::cout << pop << std::endl;
		pop.decrementGrade();
		pop.decrementGrade();
		pop.decrementGrade();
		pop.decrementGrade();
		pop.decrementGrade();
		pop.decrementGrade();
		std::cout << pop << std::endl;
		pop.decrementGrade();
		std::cout << pop << std::endl;
	}
	catch(Bureaucrat::GradeTooHighException& e)
	{
		std::cerr << "pop " << " : " << e.what() << std::endl;
	}
	catch(Bureaucrat::GradeTooLowException& e)
	{
		std::cerr << "pop " << " : " << e.what() << std::endl;
	}
	std::cout << "Grade of pop after throw" << std::endl;

	std::cout << "\nNext test : ror" << std::endl;
	Bureaucrat* ror = NULL;
	Bureaucrat* dod = NULL;
	try
	{
		ror = new Bureaucrat("ror", 4994);
	}
	catch(Bureaucrat::GradeTooHighException& e)
	{
		std::cerr << "ror " << " : " << e.what() << std::endl;
	}
	catch(Bureaucrat::GradeTooLowException& e)
	{
		std::cerr << "ror " << " : " << e.what() << std::endl;
	}
	if (ror)
	{
		std::cout << *ror << std::endl;
		ror->incrementGrade();
		std::cout << *ror << std::endl;
	}

	std::cout << "\nNext test : dod" << std::endl;
	try
	{
		dod = new Bureaucrat("dod", 4994);
	}
	catch(Bureaucrat::GradeTooHighException& e)
	{
		std::cerr << "dod " << " : " << e.what() << std::endl;
	}
	catch(Bureaucrat::GradeTooLowException& e)
	{
		std::cerr << "dod " << " : " << e.what() << std::endl;
	}
	if (dod)
	{
		std::cout << *dod << std::endl;
		dod->incrementGrade();
		std::cout << *dod << std::endl;
	}

	delete ror;
	delete dod;
	return 0;
}
