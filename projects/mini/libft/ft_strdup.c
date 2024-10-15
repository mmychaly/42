/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:58:02 by azakharo          #+#    #+#             */
/*   Updated: 2024/06/04 11:35:41 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		length;
	char	*data;

	length = ft_strlen(src);
	data = (char *)malloc((length + 1) * sizeof(char));
	if (!data)
		return (0);
	i = 0;
	while (i < length)
	{
		data[i] = src[i];
		i++;
	}
	data[length] = '\0';
	return (data);
}
