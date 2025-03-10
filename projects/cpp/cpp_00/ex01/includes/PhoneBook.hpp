#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include "Contact.hpp"

class PhoneBook
{
	public:
			PhoneBook(void);
			~PhoneBook(void);
			int	set_contact(PhoneBook *book_manager);
			Contact& get_contact(int index);
			int	get_contact(void);
			void format_get_contact(std::string str);
			void get_info_contact(int i);
			void trim_whitespace(std::string& str);

	private:
	int counter;
	Contact _contact_list[8];
};
#endif