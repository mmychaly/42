#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <string>

template<typename T, typename S, typename F>
void iter(T const & array, S const & len, F func)
{
	for (U i = 0; i < len; i++)
	{
		func(array[i]);
	}
}

#endif