#include "../includes/Form.hpp"
#include "../includes/Bureaucrat.hpp"

Form::Form(void): _name("default"), _gradeOfSigned(150), _gradeOfRequired(150), _signed(false)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(std::string name, int gradeOfSigned, int gradeOfRequired): _name(name), _gradeOfSigned(gradeOfSigned), _gradeOfRequired(gradeOfRequired), _signed(false)
{
	std::cout << "Form " << name << " constructor called" << std::endl;
	if (_gradeOfSigned > 150 || _gradeOfRequired > 150)
		throw Form::GradeTooLowException();
	else if (_gradeOfSigned < 1 || _gradeOfRequired < 1)
		throw Form::GradeTooHighException();
}

Form::Form(Form const & src):_name(src.getName()), _gradeOfSigned(src.getGradeOfSigned()), _gradeOfRequired(src.getGradeOfRequired()), _signed(src.isSigned())
{
	std::cout << "Form " << src._name << " copy constructor called " << std::endl;
}
Form & Form::operator=(Form const & src)
{
	if (this != &src)
	{
		_signed = src._signed;
	}
	return *this;
}

Form::~Form(void)
{
	std::cout << "Form " << this->_name << " destructor called " << std::endl;
}

std::string Form::getName(void) const
{
	return (_name);
}

int Form::getGradeOfSigned(void) const
{
	return (_gradeOfSigned);
}

int Form::getGradeOfRequired(void) const
{
	return (_gradeOfRequired);
}

void Form::beSigned(Bureaucrat & src)
{
	if (src.getGrade() > _gradeOfSigned)
		throw Form::GradeTooLowException();
	else
		_signed = true;
}

bool Form::isSigned(void) const
{
	return _signed;
}
const char* Form::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high.");
}

const char* Form::GradeTooLowException::what(void) const throw ()
{
	return ("Grade too low.");
}

std::ostream & operator<<(std::ostream & out, Form const & src)
{
	out << "Form " << src.getName() << " is "<< (src.isSigned() ? "signed" : "unsigned") << ": grade for signed is " << src.getGradeOfSigned() << ". Grade for required is " << src.getGradeOfRequired() << std::endl;
	return out;
}