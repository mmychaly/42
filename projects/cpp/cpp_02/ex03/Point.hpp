#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include "Fixed.hpp"
#include <cmath>

class Point
{
	public:
		Point(void);
		Point(float nb_1, float nb_2);
		Point(Point const & obj);
		Point & operator=( Point const & obj);
		~Point(void);

		Fixed const  getX( void ) const;
		Fixed const  getY( void ) const;
	private:
		Fixed const _x;
		Fixed const _y;
};

std::ostream & operator<<(std::ostream & out, Point const & obj);

#endif