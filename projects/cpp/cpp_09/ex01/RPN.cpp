/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:03:38 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/28 21:47:44 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <string>
#include <cstdlib>

RPN::RPN(void){}

RPN::RPN(RPN const & src)
{
	*this = src;
}

RPN & RPN::operator=(RPN const & src)
{
	if (this != &src)
	{
		this->_data = src._data;
	}
	return *this;
}

RPN::~RPN(void){}

bool RPN::checkData(const std::string & data)
{
	int counterDigit = 0;
	int counterOperator = 0;
	if (data.empty())
		return false;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!isdigit(data[i]))
		{
			if ((data[i] == '/' || data[i] == '*' || data[i] == '+' || data[i] == '-') && ((i + 1 < data.size() && data[i+1] == ' ') || i + 1 == data.size()))
			{
				counterOperator++;
				continue;
			}	
			else if (data[i] == '-' && (i + 1 < data.size() && isdigit(data[i + 1])) && ((i + 2 < data.size() && data[i+2] == ' ') || i + 2 == data.size()))
					continue;
			else if (data[i] == ' ')
				continue;
			else
				return false;

		}
		if (isdigit(data[i]))
		{ 
			if ((i + 1 < data.size() && data[i+1] == ' ') || i + 1 == data.size())
			{
				counterDigit++;
				continue;
			}
			else
				return false;
		}
	}
	if (counterDigit < 2)
		return false;
	if (counterOperator != counterDigit - 1)
		return false;
	return true;
}

void RPN::executeRPN(const std::string & data)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (isdigit(data[i]))
		{
			_data.push(data[i] - '0');
			continue;
		}
		if (data[i] == ' ')
			continue;
		if (data[i] == '-' && (i + 1 < data.size() && isdigit(data[i + 1])))
		{
			_data.push(-1 * (data[i+1] - '0'));
			i++;
			continue;
		}
		if (data[i] == '-' || data[i] == '+' || data[i] == '/' || data[i] == '*')
		{
			if (_data.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			int seconde = _data.top();
			_data.pop();
			int first= _data.top();
			_data.pop();
			switch (data[i])
			{
			case '-':
				_data.push(first - seconde);
				break;
			case '+':
				_data.push(first + seconde);
				break;
			case '/':
				if (seconde == 0)
				{
					std::cerr << "Error: Division by zero" << std::endl;
					return ;
				}
				_data.push(first / seconde);
				break;
			case '*':
				_data.push(first * seconde);
				break;
			}
		}
	}
	if (_data.size() == 1)
		std::cout << _data.top() << std::endl;
	else
		std::cerr << "Error" << std::endl;
}