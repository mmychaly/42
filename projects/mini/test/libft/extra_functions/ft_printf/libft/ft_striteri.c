/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:55:49 by azakharo          #+#    #+#             */
/*   Updated: 2024/06/04 11:04:05 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		f(i, s);
		s++;
		i++;
	}
}

/*#include <stdio.h>

void	print_index_and_char(unsigned int index, char *ch)
{
	printf("Index %u: %c\n", index, *ch);
}

int	main(void)
{
	char	str[] = "hello";
	ft_striteri(str, print_index_and_char);
	return (0);
}*/
