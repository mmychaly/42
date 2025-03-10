#include <iostream>
#include <string>
#include "PhoneBook.hpp"


int main(int argc, char **argv)
{
	PhoneBook book_manager;
	std::string input;
	while (1)
	{
		std::cout << "You is in the main menu, enter the command:" << std::endl;
		if (!std::getline(std::cin, input))
			return (0);
		if (input == "ADD")
		{
			if (book_manager.set_contact(&book_manager) == 1)
				return (1);				
		}
		else if (input == "SEARCH")
		{
			if (book_manager.get_contact() == 1)
				return (1);
		}
		else if (input == "EXIT")
		{
			return (0);
		}
		else 
		{
			std::cout << "Please enter one of the following:" << std::endl;
			std::cout << "ADD: add a contact" << std::endl;
			std::cout << "SEARCH: search contact list" << std::endl;
			std::cout << "EXIT: exit to program" << std::endl;
		}
	}
	return 0;
}
