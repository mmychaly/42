/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 04:06:15 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/28 04:07:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <string>

std::string upper_and_print(std::string arg)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		char temp = arg[i];
		arg[i] = std::toupper(temp);
	}
	return arg;
}

int main(int argc, char **argv)
{
	std::string text;
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		text += upper_and_print(argv[i]);
	}
	std::cout << text << std::endl;
	return 0;
}
