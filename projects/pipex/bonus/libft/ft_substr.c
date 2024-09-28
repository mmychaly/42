/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikerf <mikerf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:29:39 by mmychaly          #+#    #+#             */
/*   Updated: 2024/05/31 02:48:55 by mikerf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		str_len;
	size_t		total;
	char		*sub_str;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		total = str_len - start;
	else
		total = len;
	sub_str = malloc(sizeof(char) * (total + 1));
	if (sub_str == NULL)
		return (NULL);
	str_len = 0;
	while (str_len < total)
	{
		sub_str[str_len] = ((char *)s)[start + str_len];
		str_len++;
	}
	sub_str[str_len] = '\0';
	return (sub_str);
}
