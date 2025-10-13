#include "bigint.hpp"

bigint::bigint()
{
	digit.push_back(0);
}

bigint::bigint(unsigned long long nb)
{
	if (nb == 0)
		digit.push_back(0);
	unsigned long long tmp = nb;
	while (tmp > 0)
	{
		digit.push_back(tmp % 10);
		tmp /= 10;
	}
}

bigint::bigint(const std::string& str)
{
	digit.clear();
	if (str.empty())
	{
		digit.push_back(0);
	}

	for (int i = str.size() - 1; i >= 0; --i)
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
	remove_zero();
}

bigint::bigint(const bigint& obj)
{
	*this = obj;
}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& obj)
{
	if (this != &obj)
	{
		digit = obj.digit;
	}
	return *this;
}

bigint bigint::operator+(const bigint& obj) const
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

bigint bigint::operator-(const bigint& obj) const
{
	if (*this < obj)
		return bigint(0);
	
	bigint res;
	res.digit = digit;

	int borrow = 0;
	for (size_t i = 0; i < res.digit.size(); ++i)
	{
		int sum;
		if (i < obj.digit.size())
			sum = obj.digit[i];
		res.digit[i] -= sum + borrow;
		if (res.digit[i] < 0)
		{
			res.digit[i] += 10;
			borrow = 1;
		}
		else
			borrow = 0;
	}
	res.remove_zero();
	return res;
}

bigint& bigint::operator+=(const bigint& obj)
{
	*this = *this + obj;
	return *this;
}

bigint& bigint::operator-=(const bigint& obj)
{
	*this = *this - obj;
	return *this;
}

bigint bigint::operator>>(size_t n) const
{
	bigint res(*this);
	res >>= n;
	return res; 
}

bigint bigint::operator<<(size_t n) const
{
	bigint res(*this);
	res <<= n;
	return res;
}

bigint& bigint::operator>>=(size_t n)
{
	if (n >= digit.size())
	{
		digit.clear();
		digit.push_back(0);
		return *this;
	}
	digit.erase(digit.begin(), digit.begin() + n);
	return *this;
}

bigint& bigint::operator<<=(size_t n)
{
	if (*this != bigint(0))
		digit.insert(digit.begin(), n, 0);
	return *this;
}

bigint& bigint::operator++(void)
{
	*this += bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint res(*this);
	++(*this);
	return res;
}

bool bigint::operator==(const bigint& obj) const
{
	return (digit == obj.digit);
}

bool bigint::operator!=(const bigint& obj) const
{
	return !(*this == obj);
}

bool bigint::operator>(const bigint& obj) const
{
	return obj < *this;
}

bool bigint::operator<(const bigint& obj) const
{
	if (digit.size() != obj.digit.size())
		return digit.size() < obj.digit.size();
	for (int i = digit.size() - 1; i >= 0; --i)
	{
		if (digit[i] != obj.digit[i])
			return digit[i] < obj.digit[i];
	}
	return false;
}

bool bigint::operator>=(const bigint& obj) const
{
	return !(*this < obj);
}

bool bigint::operator<=(const bigint& obj) const
{
	return !(*this > obj);
}

void bigint::remove_zero(void)
{
	while (digit.size() > 1 && digit.back() == 0)
	{
		digit.pop_back();
	}
}

std::vector<int> bigint::get_digit(void) const
{
	return digit;
}

std::ostream& operator<<(std::ostream& o, const bigint& obj)
{
	std::vector<int> tmp = obj.get_digit();
	for (int i = tmp.size() - 1; i >= 0; --i)
	{
		o << tmp[i];
	}
	return o;
}