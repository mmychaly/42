#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class bigint
{
	public:
		bigint();
		bigint(unsigned long long nbr);
		bigint(const std::string& str);
		bigint(const bigint& src);
		bigint& operator=(const bigint& src);
		~bigint();

		
		bigint	operator+(const bigint& obj) const;
		bigint	operator-(const bigint& obj) const;

		bigint&	operator+=(const bigint& obj);
		bigint&	operator-=(const bigint& obj);

		bigint&	operator++(void);
		bigint	operator++(int);

		bigint	operator<<(size_t nb) const;
		bigint	operator>>(size_t nb) const;
		bigint&	operator<<=(size_t nb);
		bigint&	operator>>=(size_t nb);

		bool	operator==(const bigint& obj) const;
		bool	operator<=(const bigint& obj) const;
		bool	operator>=(const bigint& obj) const;
		bool	operator<(const bigint& obj) const;
		bool	operator>(const bigint& obj) const;
		bool	operator!=(const bigint& obj) const;

		void remove_first_zero();
		std::vector<int> get_digit() const;
	private:
		std::vector<int> digit;

};

	std::ostream& operator<<(std::ostream& o, const bigint& obj);

#endif