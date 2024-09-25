/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:02:08 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/25 01:27:15 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_error(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;
	int		i;

	i = 0;
	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1] != '\0')
		len_s1++;
	while (s2[len_s2] != '\0')
		len_s2++;
	str = malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	len_s1 = 0;
	while (s2[len_s1] != '\0')
		str[i++] = s2[len_s1++];
	str[i] = '\0';
	return (str);
}


char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL || *s == '\0')
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		str_len;
	size_t		total;
	char		*sub_str;

	str_len = 0;
	while (s[str_len] != '\0')
		str_len++;
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
