/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:49:05 by azakharo          #+#    #+#             */
/*   Updated: 2024/06/13 22:12:59 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && is_charset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_charset(s1[end - 1], set))
		end--;
	trimmed_str = malloc(sizeof(char) * (end - start + 1));
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		trimmed_str[i] = s1[start + i];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	set[] = ",.;-a";
	char	s1[] = ".;,Hello world ----aaaa";
	char	*joined_str;

	joined_str = ft_strtrim(s1, set);
	if (joined_str)
	{
		printf("%s\n", joined_str);
		free(joined_str);
	}
}*/
