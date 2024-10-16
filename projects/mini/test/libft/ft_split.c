/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:17:19 by azakharo          #+#    #+#             */
/*   Updated: 2024/06/13 22:30:02 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	total_size(const char *str, char charset)
{
	int	count;
	int	is_substring;

	is_substring = 0;
	count = 0;
	while (*str != '\0')
	{
		if (is_charset(*str, charset))
		{
			if (is_substring == 1)
			{
				is_substring = 0;
				count++;
			}
		}
		else if (!is_substring)
			is_substring = 1;
		str++;
	}
	if (is_substring == 1)
		count++;
	return (count);
}

static char	*alloc_word(const char *str, int length)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (length + 1));
	if (!word)
		return (NULL);
	while (i < length)
	{
		word[i] = str[i];
		i++;
	}
	word[length] = '\0';
	return (word);
}

static char	*get_next_word(const char **s, char c)
{
	int			len;
	const char	*start;

	len = 0;
	while (is_charset(**s, c) && **s)
		(*s)++;
	start = *s;
	while (!is_charset((*s)[len], c) && (*s)[len])
		len++;
	*s += len;
	return (alloc_word(start, len));
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	int		i;

	word_count = total_size(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&s, c);
		if (!result[i++])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
	}
	result[i] = NULL;
	return (result);
}

/*#include <stdio.h>

int	main(void)
{
	char	str[] = "+++foo+bar+moo+++";
	char	charset;
	char	**result;

	charset = '+';
	result = ft_split(str, charset);
	if (result == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	for (int i = 0; i < 4; i++)
	{
		printf("%s\n", result[i]);
	}
	free(result);
}*/
