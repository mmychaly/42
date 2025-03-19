#include "Point.hpp"
#include "Fixed.hpp"

float my_abs_float(float value)
{
    return (value < 0 ? -value : value);
}

Fixed take_area(Point const a, Point const b, Point const c)
{	
	Fixed area(Fixed(0.5f) * ((a.getX() * (b.getY() - c.getY())) + (b.getX() * (c.getY() - a.getY())) + (c.getX() * (a.getY() - b.getY()))));
	return Fixed(my_abs_float(area.toFloat()));
}

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
	Fixed abc;
	Fixed pab;
	Fixed pbc;
	Fixed pca;

	abc = take_area(a, b, c);
	pab = take_area(point, a, b);
	pbc = take_area(point, b, c);
	pca = take_area(point, c, a);

	// std::cout << "abc " << abc << std::endl;
	// std::cout << "pab " << pab << std::endl;
	// std::cout << "pbc " << pbc << std::endl;
	// std::cout << "pca " << pca << std::endl;

	if (abc == (pab + pbc + pca))
	{
		if (pab > 0 && pbc > 0 && pca > 0)
			return true;
	}
	return false;
}