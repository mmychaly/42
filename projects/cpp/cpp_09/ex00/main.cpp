/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:04:22 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/28 21:04:23 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"



int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::cerr << "Error: Wrong number of arguments!" << std::endl;
		return 1;
	}
	else if (argc < 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	else
	{
		BitcoinExchange x;
		if (x.conversData() == false)
		{
			std::cerr << "Error: bad data." << std::endl;
			return (1);
		}
		x.defineActualPrice(argv[1]);
	}

	return 0;
}
