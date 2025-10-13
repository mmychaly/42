#include "vect2.hpp"

vect2::vect2(): x(0), y(0) {}

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

vect2 vect2::operator*(int num) const
{
	return vect2((x * num), (y * num));
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

vect2& vect2::operator*=(int num)
{
	x *= num;
	y *= num;
	return *this;
}

vect2& vect2::operator++()
{
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 res(*this);
	++(*this);
	return res;
}

vect2& vect2::operator--()
{
	--x;
	--y;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 res(*this);
	--(*this);
	return res;
}

vect2 vect2::operator-() const
{
	return vect2(-x, -y);
}

int& vect2::operator[](int num)
{
	if (num == 0)
		return x;
	return y;
}

const int& vect2::operator[](int num) const
{
	if (num == 0)
		return x;
	return y;
}

bool vect2::operator==(const vect2& obj) const
{
	return  (x == obj.x && y == obj.y);
}

bool vect2::operator!=(const vect2& obj) const
{
	return !(*this == obj);
}

int vect2::get_x(void) const
{
	return x;
}

int vect2::get_y(void) const
{
	return y;	
}

vect2 operator*(int num, const vect2& obj)
{
	return obj * num;
}

std::ostream& operator<<(std::ostream& o, const vect2& obj)
{
	o << "{" << obj.get_x() << ", " << obj.get_y() << "}";
	return o;
}