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

		bigint& operator++();
		bigint operator++(int);

		bigint operator>>(t_size n) const;
		bigint operator<<(t_size n) const;

		bigint& operator>>=(t_size n);
		bigint& operator<<=(t_size n);

		bool operator==(const bigint& obj) const;
		bool operator!=(const bigint& obj) const;
		bool operator<(const bigint& obj) const;
		bool operator>(const bigint& obj) const;
		bool operator<=(const bigint& obj) const;
		bool operator>=(const bigint& obj) const;

		std::vector<int> get_digit() const;
		void remov_first_zero();

	private:
		std::vector<int> digit;
};

	std::ostream& operator<<(std::ostream& o, const bigint& obj) const;
#endif