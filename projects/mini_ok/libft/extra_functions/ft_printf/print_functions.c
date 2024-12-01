/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:54:54 by azakharo          #+#    #+#             */
/*   Updated: 2024/09/27 01:26:30 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_printchar_fd(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_string(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}

int	ft_print_number(int number)
{
	int		count;
	char	c;

	count = 0;
	if (number == -2147483648)
		return (ft_print_string("-2147483648"));
	if (number < 0)
	{
		count += ft_printchar_fd('-');
		number = -number;
	}
	if (number >= 10)
	{
		count += ft_print_number(number / 10);
	}
	c = (number % 10) + '0';
	count += ft_printchar_fd(c);
	return (count);
}
