/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:04:34 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/28 21:04:35 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <exception>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const & src);
		BitcoinExchange & operator=(BitcoinExchange const & src);
		~BitcoinExchange(void);

		bool checkDate(const std::string& date);
		bool conversData(void);
		bool checkValue(std::string value, int flag);
		void defineActualPrice(const std::string & input);
	private:
		std::map<std::string, float> _data;
};

#endif