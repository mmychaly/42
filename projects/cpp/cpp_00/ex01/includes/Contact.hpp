#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>
# include <cctype>
class Contact
{
	public:
			Contact(void);
			~Contact(void);

			void set_first_name(std::string str);
			void set_last_name(std::string str);
			void set_nickname(std::string str);
			int set_number(std::string str);
			void set_secret(std::string str);
			std::string get_first_name(void) const;
			std::string get_last_name(void) const;
			std::string get_nickname(void) const;
			std::string get_number(void) const;
			std::string get_secret(void) const;
			void not_empty(void);
			bool get_is_empty(void);
			void set_all_null(void);

	private:
	std::string _first_name;
	std::string _last_name;
	std::string _nickname;
	std::string _number;
	std::string _secret;
	bool _is_empty;

};
#endif