#include "Point.hpp"
#include "Fixed.hpp"

Point::Point(void): _x(0), _y(0) {}
Point::Point(float const nb_x, float const nb_y): _x(nb_x), _y(nb_y) {}

Point::Point(Point const & obj) : _x(obj.getX()), _y(obj.getY()) {}

Point& Point::operator=(Point const & obj)
{
	std::cerr << "Error: cannot change Point const attributes. " << std::endl;
	(void)obj;
	return (*this);
}

Point::~Point(void) {}

Fixed const Point::getX( void ) const
{
	return this->_x;
}

Fixed const Point::getY( void ) const
{
	return this->_y;
}

std::ostream & operator<<(std::ostream & out, Point const & obj)
{
	out << obj.getX();
	out << " ";
	out << obj.getY();
	return out;
}