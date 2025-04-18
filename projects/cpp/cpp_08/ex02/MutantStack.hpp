#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <list>

template<typename T, typename C = std::deque<T> >
class MutantStack: public std::stack<T, C>
{
	public:
		typedef typename std::stack<T, C>::container_type::iterator iterator;
		typedef typename std::stack<T, C>::container_type::const_iterator const_iterator;
		typedef typename std::stack<T, C>::container_type::reverse_iterator reverse_iterator;
		typedef typename std::stack<T, C>::container_type::const_reverse_iterator const_reverse_iterator;
		MutantStack(void): std::stack<T, C>() {}

		MutantStack(MutantStack<T, C> const & src) : std::stack<T, C>() 
		{
			*this = src;
		}

		MutantStack& operator=(MutantStack<T, C> const & src)
		{
			if (this != &src)
			{
				this->c = src.c;
			}
			return (*this);
		}

		~MutantStack(){}

		iterator begin(void)
		{
			return (this->c.begin());
		}

		iterator end(void)
		{
			return (this->c.end());
		}

		const_iterator begin(void) const
		{
			return (this->c.begin());
		}

		const_iterator end(void) const
		{
			return (this->c.end());
		}

		reverse_iterator rbegin(void)
		{
			return (this->c.rbegin());
		}

		reverse_iterator rend(void)
		{
			return (this->c.rend());
		}

		const_reverse_iterator rbegin(void) const
		{
			return (this->c.rbegin());
		}

		const_reverse_iterator rend(void) const
		{
			return (this->c.rend());
		}
};

#endif