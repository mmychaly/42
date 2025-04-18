#include "Span.hpp"
#include <algorithm>

Span::Span(): _size(0) {}

Span::Span(unsigned int size): _size(size) {}

Span::Span(const Span& src)
{
	*this = src;
}
Span& Span::operator=(const Span& src)
{
	if (this != &src)
	{
		_size = src._size;
		_array = src._array;
	}
	return (*this);
}

Span::~Span() {}

void Span::addNumber(int nb)
{
	if (_array.size() == _size)
	{
		throw Span::FullArrayException();
	}
	else
		_array.push_back(nb);
}

int Span::shortestSpan(void)
{
	if (_array.size() < 2)
		throw Span::TooShortArrayException();

	std::vector<int> temp = _array;

	std::sort(temp.begin(), temp.end());

	int minDeff = (temp[1] - temp[0]);

	for (size_t i = 0; i < (temp.size() - 1); i++)
	{
		if ((temp[i + 1] - temp[i]) < minDeff)
			minDeff = (temp[i + 1] - temp[i]);
	}
	return (minDeff);
}


int Span::longestSpan(void)
{
	if (_array.size() < 2)
		throw Span::TooShortArrayException();
	std::vector<int>::const_iterator itMin = std::min_element(_array.begin(), _array.end());
	std::vector<int>::const_iterator itMax = std::max_element(_array.begin(), _array.end());

	return (*itMax - *itMin);
}


const char*  Span::FullArrayException::what() const throw()
{
	return ("Array is full!");
}

const char* Span::TooShortArrayException::what() const throw()
{
	return ("Array is too short!");
}

std::vector<int>& Span::getArray(void)
{
	return _array;
}
unsigned int Span::getSize(void)
{
	return _size;
}

std::ostream & operator<<(std::ostream & out, Span & src)
{
	for (size_t i = 0; i < src.getArray().size(); i++)
	{
		out << "index : " << i << " Value: " <<src.getArray()[i] << std::endl;
	}
	out << "Size is " << src.getSize() << std::endl;;
	return out;
}