#include "Fixed.hpp"

Fixed::Fixed(void): _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const & copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed::Fixed(int const nb): _value(nb << _bits)
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(float const nb): _value(roundf(nb * (1 << _bits)))
{
	std::cout << "Float constructor called" << std::endl;
}

Fixed& Fixed::operator=(Fixed const & other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other.getRawBits();
	return *this;	
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
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

std::ostream & operator<<(std::ostream & out, Fixed const & obj)
{
	out << obj.toFloat();
	return out;
}