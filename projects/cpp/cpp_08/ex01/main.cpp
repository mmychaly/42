#include "Span.hpp"


int main(void)
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::vector<int> x;
	x.push_back(50);
	x.push_back(1);
	x.push_back(501);
	x.push_back(2);
	Span y(4);
	y.RangeAdd(x.begin(), x.end());
	std::cout << y.shortestSpan() << std::endl;
	std::cout << y.longestSpan() << std::endl;
	std::cout << y;
	return 0;
}