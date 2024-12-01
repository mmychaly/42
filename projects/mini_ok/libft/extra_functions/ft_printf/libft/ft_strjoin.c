/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:36:54 by azakharo          #+#    #+#             */
/*   Updated: 2024/05/30 21:21:10 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result_string;
	int		total_len;
	size_t	i;
	size_t	j;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	result_string = malloc(sizeof(char) * (total_len + 1));
	if (!result_string)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		result_string[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result_string[j++] = s2[i++];
	result_string[j] = '\0';
	return (result_string);
}

/*#include <stdio.h>

int	main(void)
{
	char	s2[] = "";
	char	s1[] = "Hello, ";
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	if (joined_str)
	{
		printf("%s\n", joined_str);
		free(joined_str);
	}
}
*/