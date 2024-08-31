/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexadecimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:11:05 by mmychaly          #+#    #+#             */
/*   Updated: 2024/06/09 07:17:39 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_hexadecimal(unsigned int nbr, char symb, int *len)
{
	long	nb;
	long	mod;
	char	*base_low;
	char	*base_up;

	nb = (long) nbr;
	base_low = "0123456789abcdef";
	base_up = "0123456789ABCDEF";
	if (nb >= 16)
		ft_put_hexadecimal(nb / 16, symb, len);
	mod = nb % 16;
	if (symb == 'x')
		write (1, &base_low[mod], 1);
	else
		write (1, &base_up[mod], 1);
	(*len)++;
}
