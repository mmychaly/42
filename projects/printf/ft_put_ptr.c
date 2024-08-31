/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:08:20 by mmychaly          #+#    #+#             */
/*   Updated: 2024/06/09 07:02:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check(void *ptr, int *len, unsigned long nbr, int *i)
{
	if (ptr == NULL)
	{
		write (1, "(nil)", 5);
		*len += 5;
		return (1);
	}
	while (nbr > 0)
	{
		nbr = nbr / 16;
		(*i)++;
	}
	return (0);
}

void	ft_put_ptr(void *ptr, int *len)
{
	int				i;
	unsigned long	nbr;
	char			str[24];

	i = 0;
	nbr = (unsigned long)ptr;
	if (ft_check(ptr, len, nbr, &i) == 1)
		return ;
	write (1, "0x", 2);
	*len += 2;
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = "0123456789abcdef"[nbr % 16];
		nbr = nbr / 16;
		i--;
	}
	ft_put_str(str, len);
}
