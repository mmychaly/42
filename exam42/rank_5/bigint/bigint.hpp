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
		bigint(unsigned long long nb);
		bigint(const std::string& str);
		bigint(const bigint& obj);
		~bigint();

		bigint& operator=(const bigint& obj);

		bigint operator+(const bigint& obj) const;
		bigint operator-(const bigint& obj) const;

		bigint& operator+=(const bigint& obj);
		bigint& operator-=(const bigint& obj);

		bigint operator>>(size_t n) const;
		bigint operator<<(size_t n) const;

		bigint& operator>>=(size_t n);
		bigint& operator<<=(size_t n);

		bigint& operator++(void);
		bigint operator++(int);

		bool operator==(const bigint& obj) const;
		bool operator!=(const bigint& obj) const;
		bool operator>(const bigint& obj) const;
		bool operator<(const bigint& obj) const;
		bool operator>=(const bigint& obj) const;
		bool operator<=(const bigint& obj) const;

		void remove_zero(void);
		std::vector<int> get_digit(void) const;

	private:
		std::vector<int> digit;
};

	std::ostream& operator<<(std::ostream& o, const bigint& obj);

#endif