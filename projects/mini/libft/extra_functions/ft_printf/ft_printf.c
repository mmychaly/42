/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:15:47 by azakharo          #+#    #+#             */
/*   Updated: 2024/09/27 00:50:16 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>

int	print_varuable(va_list args, char letter)
{
	int	count;

	count = 0;
	if (letter == 'c')
		count += ft_printchar_fd(va_arg(args, int));
	else if (letter == 's')
		count += ft_print_string(va_arg(args, char *));
	else if (letter == 'd')
		count += ft_print_number(va_arg(args, int));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += print_varuable(args, str[i + 1]);
			i++;
		}
		else
			count += ft_printchar_fd(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	// char zidan[] = "zidanovich";
	int num = 42;
	int result = ft_printf("KARAMZIN %d\n", num);
	printf("Count : %d", result);
}
*/