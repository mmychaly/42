#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <iostream>

class Brain
{
	public:
		Brain(void);
		Brain(Brain const & src);
		Brain & operator=(Brain const & src);
		~Brain(void);

		const std::string* get_all_ideas(void);
		std::string get_idea(int index);
		void set_idea(std::string str);

	private:
		std::string ideas[100];
};

#endif