#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y): x(x), y(y) {}

vect2::vect2(const vect2& obj)
{
	*this = obj;
}

vect2::~vect2() {}

vect2& vect2::operator=(const vect2& obj)
{
	if (this != &obj)
	{
		x = obj.x;
		y = obj.y;
	}
	return *this;
}

vect2 vect2::operator+(const vect2& obj) const
{
	return vect2(x + obj.x, y + obj.y);
}

vect2 vect2::operator-(const vect2& obj) const
{
	return vect2(x - obj.x, y - obj.y);
}

vect2 vect2::operator*(int scalar) const
{
	return vect2(x * scalar, y * scalar);
}

vect2& vect2::operator+=(const vect2& obj)
{
	x += obj.x;
	y += obj.y;
	return *this;
}

vect2& vect2::operator-=(const vect2& obj)
{
	x -= obj.x;
	y -= obj.y;
	return *this;
}

vect2& vect2::operator*=(int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

vect2 vect2::operator-(void) const
{
	return vect2(-x, -y);
}

vect2& vect2::operator--(void)
{
	--x;
	--y;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 tmp(*this);
	--(*this);
	return tmp;
}

vect2& vect2::operator++(void)
{
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 tmp(*this);
	++(*this);
	return tmp;
}

bool vect2::operator==(const vect2& obj) const
{
	return (x == obj.x && y == obj.y);
}

bool vect2::operator!=(const vect2& obj) const
{
	return !(*this == obj);
}

int& vect2::operator[](int index)
{
	if (index == 0)
		return x;
	return y;
}

const int& vect2::operator[](int index) const
{
	if (index == 0)
		return x;
	return y;
}


vect2 operator*(int scalar, const vect2& obj)
{
	return  obj * scalar;
}

std::ostream& operator<<(std::ostream& o, const vect2& obj)
{
	o << "{" << obj[0] << ", " << obj[1] << "}";
	return o;
}
