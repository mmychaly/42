#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class Span 
{
	public:
		Span();
		Span(unsigned int size);
		Span(const Span&);
		Span& operator=(const Span&);
		~Span();

		template<typename Iterator>
		void RangeAdd(Iterator begin, Iterator end)
		{
			if (begin > end)
        		throw std::runtime_error("Invalid iterator range!");
			if (_array.size() + std::distance(begin, end) > _size)
				throw std::runtime_error("To many numbers to add!");
			_array.insert(_array.end(), begin, end);
		}

		void addNumber(int nb);
		int shortestSpan(void);
		int longestSpan(void);

		class FullArrayException: public std::exception
		{
			public:
			virtual const char* what() const throw();
		};

		class TooShortArrayException: public std::exception
		{
			public:
			virtual const char* what() const throw();
		};

		std::vector<int>& getArray(void);
		unsigned int getSize(void);

	private:
		std::vector<int> _array;
		unsigned int _size;
};

std::ostream & operator<<(std::ostream & out, Span & src);

#endif