/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:04:10 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/28 21:04:11 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong number of arguments!" << std::endl;
		return 1;
	}
	else
	{
		RPN x;
		if (!x.checkData(argv[1]))
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		x.executeRPN(argv[1]);
	}

	return 0;
}