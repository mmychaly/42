/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikerf <mikerf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:31:39 by mmychaly          #+#    #+#             */
/*   Updated: 2024/05/31 04:29:07 by mikerf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, (len_s1 + 1));
	ft_strlcpy(&str[len_s1], s2, (len_s2 + 1));
	return (str);
}
