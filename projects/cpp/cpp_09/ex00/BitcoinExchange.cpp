/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:04:41 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/28 21:04:42 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & src) 
{
	*this = src;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & src)
{
	if (this != &src)
	{
		_data = src._data;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {}


bool BitcoinExchange::checkDate(const std::string& date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); i++)
	{
		if (!isdigit(date[i]))
		{
			if (i == 4 || i == 7)
				continue;
			else
				return false;
		}
			
	}
	int y = std::atoi(date.substr(0,4).c_str());
	int m = std::atoi(date.substr(5,2).c_str());
	int d = std::atoi(date.substr(8,2).c_str());

	if (y < 1970 || y > 2025)
		return false;
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > 31)
		return false;
	if ((y == 2020 || y == 2016 || y == 2012) && m == 2 && d == 29)
		return true;
	if (m == 2 && d > 28)
		return false;
	return true;
}

bool BitcoinExchange::checkValue(std::string value, int flag)
{
	int counter = 0;
	if (value.length() == 0)
	{
		std::cerr << "Error: bad input need value." << std::endl;
		return false;
	}
	if (value[0] == '-')
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	for (size_t i = 0; i < value.size(); i++)
	{
		if (i == 0 && value[0] == '+')
			continue;
		if (!isdigit(value[i]) && value[i] != '.')
		{
			std::cerr << "Error: is not a number => " << value << std::endl;
			return false;
		}
		if (isdigit(value[i]))
			counter++;
	}
	if (counter == 0)
	{
		std::cerr << "Error: is not a number => " << value << std::endl;
		return false;
	}
	if (flag == 1)
	{
		char* end;
		errno = 0;
		float nb = std::strtof(value.c_str(), &end);
		if (errno == ERANGE) 
		{
			std::cerr << "Error: too large a number." << std::endl;
			return false;
		}
		if (nb > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			return false;
		}
	}
	return true;
}

bool BitcoinExchange::conversData(void)
{
	std::string line;
	std::string date;
	std::string value;
	std::ifstream dataFile("data.csv");
	if (!dataFile)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return false;
	}
	else
	{
		while(std::getline(dataFile, line))
		{

			if (line == "date,exchange_rate")
				continue;
			size_t pos = line.find(',');
			if (pos  != std::string::npos)
			{
				date = line.substr(0, pos);
				if (checkDate(date) == false)
				{
					std::cerr << "Error: bad input => " << date << std::endl;
					dataFile.close();
					return false;
				}
				value = line.substr(pos + 1);
				if (checkValue(value, 0) == false)
				{
					dataFile.close();
					return false;
				}	
			}
			else 
			{
				std::cerr << "Error: wrong input" << std::endl;
				dataFile.close();
				return false;
			}
			_data[date] = std::strtof(value.c_str(), NULL);
		}
	}
	dataFile.close();
	return true;
}

void BitcoinExchange::defineActualPrice(const std::string & input)
{
	std::string line;
	std::string date;
	std::string value;
	
	std::ifstream inputFile(input.c_str());
	{
		if (!inputFile)
		{
			std::cerr << "Error: could not open file." << std::endl;
			return;
		}
	}
	while(std::getline(inputFile, line))
	{
		if (line == "date | value")
			continue;
		size_t pos = line.find('|');
		if (pos  != std::string::npos)
		{
			if (line[pos + 1] != ' ' && line[pos - 1] != ' ')
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue;
			}
			date = line.substr(0, pos - 1);
			if (checkDate(date) == false)
			{
				std::cerr << "Error: bad input => " << date << std::endl;
				continue;
			}
			value = line.substr(pos + 2);
			if (checkValue(value, 1) == false )
				continue;
		}
		else 
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::map<std::string, float>::iterator it = _data.begin();
		if (_data.empty())
		{
			std::cerr << "Error: empty data" << std::endl;
			inputFile.close();
			return;
		}
		while (it != _data.end())
		{
			if (it->first == date)
			{
				float nb = std::strtof(value.c_str(), NULL);
				float totalPrice = nb * it->second;
				std::cout << date << " => " << totalPrice << std::endl;
				break ;
			}
			it++;
		}
		if ( it == _data.end())
		{
			std::map<std::string, float>::iterator itNext = _data.begin();
			it = _data.begin();
			if (date < it->first)
			{
				std::cerr << "Error: date too early => " << date << std::endl;
				continue;
			}
			while (it != _data.end())
			{
				++itNext;
				if (itNext == _data.end() || itNext->first > date)
				{
					float nb = std::strtof(value.c_str(), NULL);
					float totalPrice = nb * it->second;
					std::cout << it->first << " => " << value << " = " << totalPrice << std::endl;
					break ;
				}
				it++;
			}
		}
	}
	if (line.empty())
	{
		std::cerr << "Error: Empty file." << std::endl;
		return;
	}
	inputFile.close();
}
