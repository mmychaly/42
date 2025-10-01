#include "bigint.hpp"		
		
bigint::bigint()
{
	digit.push_back(0);
}

bigint::bigint(unsigned long long nb)
{
	digit.clear();
	if (nb == 0)
	{
		digit.push_back(0);
		return;
	}
	unsigned long long n = nb;
	while (n != 0)
	{
		digit.push_back(n % 10);
		n /= 10;
	}
}

bigint::bigint(const std::string& str)
{
	if (str.empty)
	{
		digit.push_back(0);
		return;
	}
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (isdigit(str[i]))
			digit[i] = (str[i] - '0');
		else
		{
			digit.clear();
			digit.push_back(0);
		}
	}
	remov_first_zero();
}

bigint::bigint(const bigint& obj)
{

}

bigint::~bigint()
{

}

bigint& bigint::operator=(const bigint& obj)
{

}

bigint bigint::operator+(const bigint& obj) const
{

}

bigint bigint::operator-(const bigint& obj) const
{

}

bigint& bigint::operator+=(const bigint& obj)
{

}

bigint& bigint::operator-=(const bigint& obj)
{

}

bigint& bigint::operator++()
{

}

bigint bigint::operator++(int)
{

}

bigint bigint::operator>>(t_size n) const
{

}

bigint bigint::operator<<(t_size n) const
{

}

bigint& bigint::operator>>=(t_size n)
{

}

bigint& bigint::operator<<=(t_size n)
{

}

bool bigint::operator==(const bigint& obj) const
{

}

bool bigint::operator!=(const bigint& obj) const
{

}

bool bigint::operator<(const bigint& obj) const
{

}

bool bigint::operator>(const bigint& obj) const
{

}

bool bigint::operator<=(const bigint& obj) const
{

}

bool bigint::operator>=(const bigint& obj) const
{

}

std::vector<int> bigint::get_digit() const
{

}

void bigint::remov_first_zero()
{
	while (digit.size > 1 && digit.back == 0)
		digit.pop_back();
}

std::ostream& operator<<(std::ostream& o, const bigint& obj) const
{
	std::vector<int> dig = obj.get_digit();
	for (int i = dig.size() - 1; i >= 0; ++i)
	{
		o << dig[i];
	}
	return o;
}