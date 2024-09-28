/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 01:59:55 by mikerf            #+#    #+#             */
/*   Updated: 2024/05/23 10:29:04 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i_1;
	size_t		i_2;

	i_1 = 0;
	if (little[i_1] == '\0')
		return ((char *)big);
	while ((i_1 < len) && (big[i_1] != '\0'))
	{
		i_2 = 0;
		if (big[i_1] == little[i_2])
		{
			while (little[i_2] != '\0'
				&& (big[i_1 + i_2] == little[i_2])
				&& ((i_1 + i_2) < len))
				i_2++;
			if (little[i_2] == '\0')
				return ((char *)&big[i_1]);
		}
		i_1++;
	}
	return (NULL);
}
