#include "../includes/Bureaucrat.hpp"
#include "../includes/AForm.hpp"

Bureaucrat::Bureaucrat(void): _name("Default"), _grade(150)
{
	std::cout << "Bureaucrat default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name), _grade(150)
{
	std::cout << "Bureaucrat " << name << " constructor called" << std::endl;

	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const & src): _name(src.getName()), _grade(src.getGrade())
{
	std::cout << "Bureaucrat " << src._name << " copy constructor called " << std::endl;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & src)
{
	if (this != &src)
	{
		this->_grade = src.getGrade();
	}
	return *this;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << "Bureaucrat " << this->_name << " destructor called " << std::endl;
}

std::string Bureaucrat::getName(void) const
{
	return (_name);
}

int Bureaucrat::getGrade(void) const
{
	return (_grade);
}

void Bureaucrat::incrementGrade(void)
{
	if (_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	else
		_grade--;
}

void Bureaucrat::decrementGrade(void)
{
	if ( _grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	else
		_grade++;
}

const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high.");
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Grade too low.");
}

void Bureaucrat::signForm(AForm & form)
{
	try
	{
		form.beSigned(*this);
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	}
	catch(AForm::GradeTooHighException& e)
	{
		std::cerr << this->_name << " couldn’t sign " << form.getName() << " because "<< e.what() << std::endl;
	}
	catch(AForm::GradeTooLowException& e)
	{
		std::cerr << this->_name << " couldn’t sign " << form.getName() << " because "<< e.what() << std::endl;
	}	
}

void Bureaucrat::executeForm(AForm const & form)
{
	
	try
	{
		form.execute(*this);
		std::cout << _name << " executed " << form.getName() << std::endl;
	}
	catch(const std::exception&  e)
	{
		std::cout << "Can't execute form: " << e.what() << std::endl;
	}
}

std::ostream & operator<<(std::ostream & out, Bureaucrat const & src)
{
	out << src.getName() << ",  bureaucrat grade " << src.getGrade();
	return out;
}
