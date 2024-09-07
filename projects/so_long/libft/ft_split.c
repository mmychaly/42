/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:41:00 by mikerf            #+#    #+#             */
/*   Updated: 2024/06/03 13:03:11 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strings(char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static void	ft_strwrite(char *str, char const *s, char sep, int *index)
{
	int	i_2;
	int	i;

	i_2 = 0;
	i = *index;
	while (s[i] != '\0')
	{
		if (s[i] != sep)
		{
			i_2 = 0;
			while ((s[i] != sep && s[i] != '\0'))
			{
				str[i_2] = s[i];
				i_2++;
				i++;
			}
			str[i_2] = '\0';
			*index = i;
			return ;
		}
		i++;
	}
	return ;
}

static int	ft_len_counter(char const *str, char sep, int *index)
{
	int	i;
	int	counter;

	i = *index;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep)
		{
			while ((str[i] != sep && str[i] != '\0'))
			{
				counter++;
				i++;
			}
			*index = i;
			return (counter);
		}
		i++;
	}
	return (counter);
}

static char	**ft_collect_string(char **strs, char *str, char sep, int word_nbr)
{
	int	i;
	int	i_2;
	int	len;
	int	i_3;

	i = 0;
	i_2 = 0;
	i_3 = 0;
	while (i < word_nbr)
	{
		len = ft_len_counter(str, sep, &i_2);
		strs[i] = malloc(sizeof(char) * (len + 1));
		if (strs[i] == NULL)
		{
			free_strings(strs, i);
			return (NULL);
		}
		ft_strwrite(strs[i], str, sep, &i_3);
		i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_nbr;
	char	**strs;

	i = 0;
	word_nbr = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word_nbr++;
		i++;
	}
	strs = malloc(sizeof(char *) * (word_nbr + 1));
	if (strs == NULL)
		return (NULL);
	strs[word_nbr] = NULL;
	if (word_nbr == 0)
		return (strs);
	if ((ft_collect_string(strs, (char *)s, c, word_nbr)) == NULL)
		return (NULL);
	return (strs);
}
