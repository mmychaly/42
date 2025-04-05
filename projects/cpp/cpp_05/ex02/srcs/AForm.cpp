#include "../includes/AForm.hpp"
#include "../includes/Bureaucrat.hpp"

AForm::AForm(void): _name("default"), _gradeOfSigned(150), _gradeOfRequired(150), _signed(false)
{
	std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(std::string name, int gradeOfSigned, int gradeOfRequired): _name(name), _gradeOfSigned(gradeOfSigned), _gradeOfRequired(gradeOfRequired), _signed(false)
{
	std::cout << "AForm " << name << " constructor called" << std::endl;
	if (_gradeOfSigned > 150 || _gradeOfRequired > 150)
		throw AForm::GradeTooLowException();
	else if (_gradeOfSigned < 1 || _gradeOfRequired < 1)
		throw AForm::GradeTooHighException();
}

AForm::AForm(AForm const & src):_name(src.getName()), _gradeOfSigned(src.getGradeOfSigned()), _gradeOfRequired(src.getGradeOfRequired()), _signed(src.isSigned())
{
	std::cout << "AForm " << src._name << " copy constructor called " << std::endl;
}
AForm & AForm::operator=(AForm const & src)
{
	if (this != &src)
	{
		_signed = src._signed;
	}
	return *this;
}

AForm::~AForm(void)
{
	std::cout << "AForm " << this->_name << " destructor called " << std::endl;
}

std::string AForm::getName(void) const
{
	return (_name);
}

int AForm::getGradeOfSigned(void) const
{
	return (_gradeOfSigned);
}

int AForm::getGradeOfRequired(void) const
{
	return (_gradeOfRequired);
}

void AForm::beSigned(Bureaucrat & src)
{
	if (src.getGrade() > _gradeOfSigned)
		throw AForm::GradeTooLowException();
	else
		_signed = true;
}

bool AForm::isSigned(void) const
{
	return _signed;
}
const char* AForm::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high.");
}

const char* AForm::GradeTooLowException::what(void) const throw ()
{
	return ("Grade too low.");
}

const char* AForm::NotSignedForm::what() const throw()
{
	return ("Form is not signed.");
}

std::ostream & operator<<(std::ostream & out, AForm const & src)
{
	out << "Form " << src.getName() << " is "<< (src.isSigned() ? "signed" : "unsigned") << ": grade for signed is " << src.getGradeOfSigned() << ". Grade for required is " << src.getGradeOfRequired() << std::endl;
	return out;
}