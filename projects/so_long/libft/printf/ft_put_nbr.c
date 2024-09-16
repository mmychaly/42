/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:09:36 by mmychaly          #+#    #+#             */
/*   Updated: 2024/06/09 07:02:52 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_nbr(int nbr, int *len)
{
	long	nb;
	long	mod;

	nb = nbr;
	if (nb < 0)
	{
		write(1, "-", 1);
		(*len)++;
		nb = -nb;
	}
	if (nb > 9)
		ft_put_nbr((nb / 10), len);
	mod = nb % 10 + '0';
	write (1, &mod, 1);
	(*len)++;
}
