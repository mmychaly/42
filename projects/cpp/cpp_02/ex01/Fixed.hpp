#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	public:
		Fixed(void);
		Fixed(int const nb);
		Fixed(float const nb);
		Fixed(Fixed const & copy);
		Fixed& operator=(Fixed const & copy);
		~Fixed(void);
		int getRawBits( void ) const;
		void setRawBits( int const raw );
		float toFloat( void ) const;
		int toInt( void ) const;
	
	private:
		int _value;
		static const int _bits = 8;
};

std::ostream & operator<<(std::ostream & out, Fixed const & obj);

#endif