#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <exception>
#include <vector>
#include <list>
#include <algorithm>

template<typename T>
typename  T::const_iterator easyfind(T const & array, int const & value)
{	
	typename  T::const_iterator it = std::find(array.begin(), array.end(), value);
	if (it == array.end())
		throw std::runtime_error("Element not found!");
	else
		return (it);
}

#endif