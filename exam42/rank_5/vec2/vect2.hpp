#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2& obj);
		~vect2();

		vect2& operator=(const vect2& obj);

		vect2 operator+(const vect2& obj) const;
		vect2 operator-(const vect2& obj) const;
		vect2 operator*(int num) const;

		vect2& operator+=(const vect2& obj);
		vect2& operator-=(const vect2& obj);
		vect2& operator*=(int num);

		vect2& operator++();
		vect2 operator++(int);

		vect2& operator--();
		vect2 operator--(int);

		vect2 operator-() const;

		int& operator[](int num);
		const int& operator[](int num) const;

		bool operator==(const vect2& obj) const;
		bool operator!=(const vect2& obj) const;

		int get_x(void) const;
		int get_y(void) const;

	private:
		int x;
		int y;
};

vect2 operator*(int num, const vect2& obj);
std::ostream& operator<<(std::ostream& o, const vect2& obj);

#endif