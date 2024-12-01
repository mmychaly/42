/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:06:07 by azakharo          #+#    #+#             */
/*   Updated: 2024/05/25 17:29:26 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		*p++ = (unsigned char)c;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(void) {
	char buffer[10];

	ft_memset(buffer, 'A', sizeof(buffer));

	for (int i = 0; i < sizeof(buffer); i++) {
		printf("%c ", buffer[i]);
	}
	printf("\n");

	return (0);
}*/
