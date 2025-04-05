#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>

class Bureaucrat;

class AForm
{
	public:
		AForm(void);
		AForm(std::string name, int gradeOfSigned, int gradeOfRequired);
		AForm(AForm const & src);
		AForm & operator=(AForm const & src);
		virtual ~AForm(void);
	
		virtual void execute(Bureaucrat const & executor) const = 0;
		virtual void processExecuted(void) const = 0;

		std::string getName(void) const;
		int getGradeOfSigned(void) const;
		int getGradeOfRequired(void) const;
		void beSigned(Bureaucrat & src);
		bool isSigned(void) const;

		class GradeTooHighException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class NotSignedForm: public std::exception
		{
			public:
			virtual const char* what() const throw();
		};


	private:
		const std::string _name;
		const int _gradeOfSigned;
		const int _gradeOfRequired;
		bool _signed;
};

	std::ostream & operator<<(std::ostream & out, AForm const & src);

#endif