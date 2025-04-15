#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>

template<typename T>
class Array
{
	public:
		Array(void): _array(NULL), _size(0) {}
		Array(unsigned int n):_array (new T[n]()), _size(n) {}

		Array(Array const & src): _array(NULL), _size(0)
		{
			*this = src;
		}

		Array & operator=(Array const & src)
		{
			if (this != &src)
			{
				delete[] _array;
				this->_size = src._size;
				this->_array = new T[_size];
				for (unsigned int i = 0; i < _size; i++)
				{
					_array[i] = src._array[i];
				}
			}
			return *this;
		}

		~Array(void)
		{
			delete[] _array;
		}

		T &	operator[](unsigned int index)
		{
			if (index >= _size)
				throw Array::IndexOutBounds();
			else
				return _array[index];
		}

		unsigned int size(void) const
		{
			return this->_size;
		}

		class IndexOutBounds: public std::exception
		{
			public:
				virtual const char* what(void) const throw()
				{
					return "Error: Index is out of bounds.";
				}
		};

	private:
		T* _array;
		unsigned int _size;
};

#endif