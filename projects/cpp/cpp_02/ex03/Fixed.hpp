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
		~Fixed(void);

		int getRawBits( void ) const;
		void setRawBits( int const raw );
		float toFloat( void ) const;
		int toInt( void ) const;

		Fixed& operator=(Fixed const & copy);

		bool	operator>(Fixed const & obj) const;
		bool	operator<(Fixed const & obj) const;
		bool	operator>=(Fixed const & obj) const;
		bool	operator<=(Fixed const & obj) const;
		bool	operator==(Fixed const & obj) const;
		bool	operator!=(Fixed const & obj) const;

		Fixed 	operator+(Fixed const & obj) const;
		Fixed	operator-(Fixed const & obj) const;
		Fixed	operator*(Fixed const & obj) const;
		Fixed	operator/(Fixed const & obj) const;

		Fixed&	operator++(void);
		Fixed&	operator--(void);
		Fixed	operator++(int);
		Fixed	operator--(int);

		static Fixed& min(Fixed& obj_1, Fixed& obj_2);
		static Fixed& max(Fixed& obj_1, Fixed& obj_2);
		static Fixed const & min(Fixed const & obj_1, Fixed const & obj_2);
		static Fixed const & max(Fixed const & obj_1, Fixed const & obj_2);

	private:
		int _value;
		static const int _bits = 8;
};

std::ostream & operator<<(std::ostream & out, Fixed const & obj);

#endif