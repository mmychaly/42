/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:56:12 by mikerf            #+#    #+#             */
/*   Updated: 2024/06/09 23:26:58 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_launch(char *str, va_list first, int *len, int *i)
{
	if (str[*i] == 'c')
		ft_put_symb(va_arg(first, int), len);
	else if (str[*i] == '%')
		ft_put_symb(str[*i], len);
	else if (str[*i] == 's')
		ft_put_str(va_arg(first, char *), len);
	else if (str[*i] == 'i' || str[*i] == 'd')
		ft_put_nbr(va_arg(first, int), len);
	else if (str[*i] == 'u')
		ft_put_unsigned_nbr(va_arg(first, unsigned int), len);
	else if (str[*i] == 'x' || str[*i] == 'X')
		ft_put_hexadecimal(va_arg(first, unsigned int), str[*i], len);
	else if (str[*i] == 'p')
		ft_put_ptr(va_arg(first, void *), len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	first;
	int		len;

	i = 0;
	len = 0;
	if (str == 0)
		return (-1);
	va_start (first, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			ft_check_launch((char *)str, first, &len, &i);
		}
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(first);
	return (len);
}
