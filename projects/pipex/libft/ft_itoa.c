/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:39:50 by mmychaly          #+#    #+#             */
/*   Updated: 2024/05/25 09:23:38 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(long nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		nb = -nb;
		count += 1;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nb;

	nb = (long) n;
	len = ft_counter(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		if (str[len] == '-')
			break ;
		str[len] = ((nb % 10) + 48);
		nb = nb / 10;
	}
	return (str);
}
