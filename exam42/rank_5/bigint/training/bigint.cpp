#include "bigint.hpp"

bigint::bigint()
{
	digit.push_back(0);
}

bigint::bigint(unsigned long long nbr)
{
	if (nbr == 0)
		digit.push_back(0);
	unsigned long long tmp = nbr;
	while (tmp > 0)
	{
		digit.push_back(tmp % 10);
		tmp = tmp / 10;  
	}
}

bigint::bigint(const std::string& str)
{
	digit.clear();
	if (str.empty())
	{
		digit.push_back(0);
		return;
	}
	for (int i = str.size() - 1; i >= 0 ; i--)
	{
		if (isdigit(str[i]))
			digit.push_back(str[i] - '0');
		else 
		{
			digit.clear();
			digit.push_back(0);
			return;
		}
	}
	remove_first_zero();
}

bigint::bigint(const bigint& src)
{
	this->digit = src.digit;
}

bigint& bigint::operator=(const bigint& src)
{
	if (this != &src)
	{
		this->digit = src.digit;
	}
	return *this;
}

bigint::~bigint() {}




bigint	bigint::operator+(const bigint& obj) const
{
	bigint res;
	res.digit.clear();

	int carry = 0;
	size_t n = std::max(digit.size(), obj.digit.size());
	for (size_t i = 0; i < n || carry; ++i)
	{
		int sum = carry;
		if (i < digit.size())
			sum += digit[i];
		if (i < obj.digit.size())
			sum += obj.digit[i];
		
		res.digit.push_back(sum % 10);
		carry = sum / 10;
	}
	return res;
}

bigint	bigint::operator-(const bigint& obj) const
{
	if (*this < obj)
		return bigint(0);

	bigint res = *this;
	int borrow = 0;
	for (size_t i = 0; i < res.digit.size(); ++i)
	{
		int sum;
		if (i < obj.digit.size())
			sum = obj.digit[i];
		else
			sum = 0;
		res.digit[i] -= borrow + sum;
		if (res.digit[i] < 0)
		{
			res.digit[i] += 10;
			borrow = 1;
		}
		else
			borrow = 0;
	}
	res.remove_first_zero();
	return res;
}

bigint&	bigint::operator+=(const bigint& obj)
{
	*this = *this + obj;
	return *this;
}

bigint&	bigint::operator-=(const bigint& obj)
{
	*this = *this - obj;
	return *this;
}

bigint&	bigint::operator++()
{
	bigint tmp(1);
	*this += tmp;
	return *this;
}


bigint	bigint::operator++(int)
{
	bigint tmp(*this);
	++(*this);
	return tmp;
}


bigint	bigint::operator<<(size_t nb) const
{
	bigint res = *this;
	res <<= nb;
	return res;
}

bigint	bigint::operator>>(size_t nb) const
{
	bigint res = *this;
	res >>= nb;
	return res;
}

bigint&	bigint::operator<<=(size_t nb)
{
	if (*this == bigint(0))
		return *this;
	digit.insert(digit.begin(), nb, 0);
	return *this;
}

bigint&	bigint::operator>>=(size_t nb)
{
	if (nb >= digit.size())
	{
		digit.clear();
		digit.push_back(0);
		return *this;
	}
	digit.erase(digit.begin(), digit.begin() + nb);
	return *this;
}


bool	bigint::operator==(const bigint& obj) const
{
	return digit == obj.digit;
}

bool	bigint::operator<=(const bigint& obj) const
{
	return !(*this > obj);
}

bool	bigint::operator>=(const bigint& obj) const
{
	return !(*this < obj);
}

bool	bigint::operator<(const bigint& obj) const
{
	if (this->digit.size() != obj.digit.size())
		return this->digit.size() < obj.digit.size();
	for (int i = digit.size() - 1; i >= 0; --i)
	{
		if (this->digit[i] != obj.digit[i])
			return this->digit[i] < obj.digit[i];
	}
	return false;
}

bool	bigint::operator>(const bigint& obj) const
{
	return obj < *this;
}

bool	bigint::operator!=(const bigint& obj) const
{
	return !(*this == obj);
}


void bigint::remove_first_zero(void)
{
	while (digit.size() > 1 && digit.back() == 0)
	{
		digit.pop_back();
	}

}

std::vector<int> bigint::get_digit() const
{
	return digit;
}

std::ostream& operator<<(std::ostream& o, const bigint& obj)
{
	std::vector<int> tmp = obj.get_digit();
	for (int i = tmp.size() -1 ; i >= 0; --i)
	{
		o << tmp[i];
	}
	return o;
}