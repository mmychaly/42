/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:29:12 by mmychaly          #+#    #+#             */
/*   Updated: 2024/06/09 07:16:47 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_unsigned_nbr(unsigned int nbr, int *len)
{
	unsigned int	mod;

	if (nbr > 9)
		ft_put_unsigned_nbr((nbr / 10), len);
	mod = nbr % 10 + '0';
	write (1, &mod, 1);
	(*len)++;
}
