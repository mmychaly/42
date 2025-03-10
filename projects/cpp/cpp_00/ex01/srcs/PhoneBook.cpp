# include "PhoneBook.hpp"


	PhoneBook::PhoneBook(void) : counter(0)
	{
		return;
	};

	PhoneBook::~PhoneBook(void)
	{
		return;
	};

	Contact& PhoneBook::get_contact(int index)
	{
		return _contact_list[index];
	}


	void PhoneBook::trim_whitespace(std::string& str)
	{
		size_t first = str.find_first_not_of(" \t\n\r\f\v");
		if(first == std::string::npos)
		{
			str = "";
			return;
		}
		size_t last = str.find_last_not_of(" \t\n\r\f\v");
		str = str.substr(first, (last - first + 1));
	}

	int fill_information(PhoneBook* book_manager, int i_2)
	{
		std::string input;
		while (1)
		{
			Contact &contact = book_manager->get_contact(i_2);
			if (contact.get_first_name().empty())
			{
				std::cout << "Please enter your first name" << std::endl;
				if (!std::getline(std::cin, input))
					return (1);
				book_manager->trim_whitespace(input);
				if (input.empty())
				{
					std::cerr << "Error: The line is empty." << std::endl;
					continue;
				}
				contact.set_first_name(input);
			}
			if (contact.get_last_name().empty())
			{
				std::cout << "Please enter your last name" << std::endl;
				if (!std::getline(std::cin, input))
					return (1);
				book_manager->trim_whitespace(input);
				if (input.empty())
				{
					std::cerr << "Error: The line is empty." << std::endl;
					continue;
				}
				contact.set_last_name(input);
			}
			if (contact.get_nickname().empty())
			{
				std::cout << "Please enter your nickname" << std::endl;
				if (!std::getline(std::cin, input))
					return (1);
				book_manager->trim_whitespace(input);
				if (input.empty())
				{
					std::cerr << "Error: The line is empty." << std::endl;
					continue;
				}
				contact.set_nickname(input);
			}
			if (contact.get_number().empty())
			{
				std::cout << "Please enter your number" << std::endl;
				if (!std::getline(std::cin, input))
					return (1);
				book_manager->trim_whitespace(input);
				if (input.empty())
				{
					std::cerr << "Error: The line is empty." << std::endl;
					continue;
				}
				if (contact.set_number(input) == 1)
					continue;
			}
			if (contact.get_secret().empty())
			{
				std::cout << "Please enter your darkest secret" << std::endl;
				if (!std::getline(std::cin, input))
					return (1);
				book_manager->trim_whitespace(input);
				if (input.empty())
				{
					std::cerr << "Error: The line is empty." << std::endl;
					continue;
				}
				contact.set_secret(input);
			}
			contact.not_empty();
			break;
		}
		return 0;
	};

	int	PhoneBook::set_contact(PhoneBook *book_manager)
	{
		int i_2;
		for (int i = 0; i < 8; i++)
		{
			if (_contact_list[i].get_is_empty() == true)
			{
				i_2 = i;
				break;
			}
			if (i == 7 && _contact_list[i].get_is_empty() == false)
			{
				if (counter == 8)
					counter = 0;
				i_2 = counter++;
				_contact_list[i_2].set_all_null();
				break;
			}
		}
		if (fill_information(book_manager, i_2) == 1)
			return 1;
		return (0);
	};

	void PhoneBook::get_info_contact(int i)
	{
		std::cout << _contact_list[i].get_first_name() << std::endl;
		std::cout << _contact_list[i].get_last_name() << std::endl;
		std::cout << _contact_list[i].get_nickname() << std::endl;
		std::cout << _contact_list[i].get_number() << std::endl;
		std::cout << _contact_list[i].get_secret() << std::endl;
	}
	void PhoneBook::format_get_contact(std::string str)
	{
		if (str.size() > 10 )
		{
			str.resize(9);
			str += ".";
		}
		std::cout << std::setw(10) << str << "|";
		return ;
	};

	int		PhoneBook::get_contact(void)
	{
		std::string input;
		int index;
		for (size_t i = 0; i < 8; i++)
		{
			if (i == 0 && _contact_list[i].get_is_empty() == true)
			{
				std::cerr << "Error : You have no saved contacts. Please ADD a contact and try again" << std::endl;
				return 0;
			}
			else if (i == 0 && _contact_list[i].get_is_empty() == false)
				std::cout << "   INDEX  |FIRST NAME| LAST NAME| NICKNAME |" << std::endl;
			if (_contact_list[i].get_is_empty() == false)
			{
				std::cout << std::setw(10) << i << "|";
				format_get_contact(_contact_list[i].get_first_name());
				format_get_contact(_contact_list[i].get_last_name());
				format_get_contact(_contact_list[i].get_nickname());
				std::cout << std::endl;
			}
		}
		std::cout << "Select the contact index" << std::endl;
		while(1)
		{
			int flag_error = 0;
			if (!std::getline(std::cin, input))
				return (1);
			if (input == "")
			{
				std::cerr << "Error: The index must contain numbers.Try again" << std::endl;
				continue;
			}
			for (size_t i = 0; i < input.size(); i++)
			{
				if (!std::isdigit(input[i]))
				{
					std::cerr << "Error: The index must contain only numbers.Try again" << std::endl;
					flag_error = 1;
					break;
				}	
			}
			if (flag_error == 1)
				continue;
			if (input.size() > 2)	
			{
				std::cerr << "Error: Number too large. Try again" << std::endl;
				continue;
			}
			index = std::stoi(input);
			if (index >= 0 && index <= 7 && _contact_list[index].get_is_empty() == false)
			{
				get_info_contact(index);
				return (0);
			}
			else 
				std::cerr << "Error: Wrong index try again" << std::endl;
		}
		return (0);
	};
