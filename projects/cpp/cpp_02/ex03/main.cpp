#include "Fixed.hpp"
#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	Point a(0, 0);
	Point b(4, 0);
	Point c(2, 3);
	Point point(2, 1);
	if (bsp( a, b, c, point) == true)
		std::cout << "Inside triangle" << std::endl;
	else
		std::cout << "Outside triangle" << std::endl;
	return 0;
}