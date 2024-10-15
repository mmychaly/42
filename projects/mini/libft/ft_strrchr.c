/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:48:30 by azakharo          #+#    #+#             */
/*   Updated: 2024/05/30 21:30:02 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last = NULL;

	while (*str != '\0')
	{
		if (*str == (char)c)
			last = str;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return ((char *)last);
}
