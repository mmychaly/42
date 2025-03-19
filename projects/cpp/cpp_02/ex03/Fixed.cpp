#include "Fixed.hpp"

Fixed::Fixed(void): _value(0)
{
	return;
}

Fixed::Fixed(Fixed const & copy)
{
	*this = copy;
}
Fixed::Fixed(int const nb): _value(nb << _bits)
{
	return ;
}

Fixed::Fixed(float const nb): _value(roundf(nb * (1 << _bits)))
{
	return ;
}

Fixed& Fixed::operator=(Fixed const & other)
{
	if (this != &other)
		_value = other.getRawBits();
	return *this;	
}

Fixed::~Fixed(void)
{
	return;
}

int Fixed::getRawBits(void) const
{
	return this->_value;
}

void Fixed::setRawBits( int const raw )
{
	this->_value = raw;
}

float Fixed::toFloat( void ) const
{
	return ((float)_value / (1 << _bits));
}
int Fixed::toInt( void ) const
{
	return (_value >> _bits);
}


bool	Fixed::operator>(Fixed const & obj) const
{
	return (this->getRawBits() > obj.getRawBits());
}

bool	Fixed::operator<(Fixed const & obj) const
{
	return (this->getRawBits() < obj.getRawBits());
}

bool	Fixed::operator>=(Fixed const & obj) const
{
	return (this->getRawBits() >= obj.getRawBits());
}

bool	Fixed::operator<=(Fixed const & obj) const
{
	return (this->getRawBits() <= obj.getRawBits());
}

bool	Fixed::operator==(Fixed const & obj) const
{
	return (this->getRawBits() == obj.getRawBits());
}

bool	Fixed::operator!=(Fixed const & obj) const
{
	return (this->getRawBits() != obj.getRawBits());
}


Fixed 	Fixed::operator+(Fixed const & obj) const
{
	return Fixed(this->toFloat() + obj.toFloat());
}

Fixed	Fixed::operator-(Fixed const & obj) const
{
	return Fixed(this->toFloat() - obj.toFloat());
}

Fixed	Fixed::operator*(Fixed const & obj) const
{
	return Fixed(this->toFloat() * obj.toFloat());
}

Fixed	Fixed::operator/(Fixed const & obj) const
{
	return Fixed(this->toFloat() / obj.toFloat());
}


Fixed& Fixed::operator++(void)
{
	this->_value++;
	return *this;
}

Fixed& Fixed::operator--(void)
{
	this->_value--;
	return *this;
}

Fixed	Fixed::operator++(int)
{
	Fixed temp(*this);
	++(*this);
	return temp;
}

Fixed	Fixed::operator--(int)
{
	Fixed temp(*this);
	--(*this);
	return temp;
}


Fixed& Fixed::min(Fixed& obj_1, Fixed& obj_2)
{
	if (obj_1.toFloat() <= obj_2.toFloat())
		return obj_1;
	return obj_2;
}

Fixed& Fixed::max(Fixed& obj_1, Fixed& obj_2)
{
	if (obj_1.toFloat() >= obj_2.toFloat())
		return obj_1;
	return obj_2;
}

Fixed const & Fixed::min(Fixed const & obj_1, Fixed const & obj_2)
{
	if (obj_1.toFloat() <= obj_2.toFloat())
		return obj_1;
	return obj_2;
}

Fixed const & Fixed::max(Fixed const & obj_1, Fixed const & obj_2)
{
	if (obj_1.toFloat() >= obj_2.toFloat())
		return obj_1;
	return obj_2;
}


std::ostream & operator<<(std::ostream & out, Fixed const & obj)
{
	out << obj.toFloat();
	return out;
}