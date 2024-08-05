/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikerf <mikerf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 03:26:13 by mikerf            #+#    #+#             */
/*   Updated: 2024/05/31 23:29:35 by mikerf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*symb;

	i = 0;
	symb = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			symb = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		symb = ((char *)&s[i]);
	return (symb);
}
