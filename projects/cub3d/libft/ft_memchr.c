/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 02:23:38 by mikerf            #+#    #+#             */
/*   Updated: 2024/05/22 19:11:00 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*ptr;
	unsigned char			symb;

	i = 0;
	ptr = (const unsigned char *)s;
	symb = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == symb)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
