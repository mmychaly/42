#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>

class Bureaucrat;

class Form
{
	public:
		Form(void);
		Form(std::string name, int gradeOfSigned, int gradeOfRequired);
		Form(Form const & src);
		Form & operator=(Form const & src);
		virtual ~Form(void);
	
		std::string getName(void) const;
		int getGradeOfSigned(void) const;
		int getGradeOfRequired(void) const;
		void beSigned(Bureaucrat & src);
		bool isSigned(void) const;

		virtual void execute(Bureaucrat const & executor) const;
		virtual void processExecuted(void) const;
		virtual std::string getTarget(void) const;
		
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

	std::ostream & operator<<(std::ostream & out, Form const & src);

#endif