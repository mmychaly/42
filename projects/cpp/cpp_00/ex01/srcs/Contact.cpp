#include "Contact.hpp"

Contact::Contact(void): _is_empty(true)
{
	return;
};
Contact::~Contact(void)
{
	return;
};

void Contact::set_first_name(std::string str)
{
	this->_first_name = str;
};

void Contact::set_last_name(std::string str)
{
	this->_last_name = str;
};

void	Contact::set_nickname(std::string str)
{
	this->_nickname = str;
};

int	Contact::set_number(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cerr << "Error: The phone number must contain only numbers." << std::endl;
			return (1);
		}	
	}
	this->_number = str;
	return (0);
};

void Contact::set_secret(std::string str)
{
	this->_secret = str;
};

std::string Contact::get_first_name(void) const
{
	return (this->_first_name);
};

std::string Contact::get_last_name(void) const
{
	return (this->_last_name);
};

std::string Contact::get_nickname(void) const
{
	return (this->_nickname);
};

std::string Contact::get_number(void) const
{
	return (this->_number);
};

std::string Contact::get_secret(void) const
{
	return (this->_secret);
};

void Contact::not_empty(void)
{
	this->_is_empty = false;
};

bool Contact::get_is_empty(void)
{
	return (this->_is_empty);
};

void Contact::set_all_null(void)
{
	this->_first_name = "";
	this->_last_name = "";
	this->_nickname = "";
	this->_number = "";
	this->_secret = "";
}