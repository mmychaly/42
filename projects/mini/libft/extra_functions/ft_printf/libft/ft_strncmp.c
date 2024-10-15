/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakharo <zarart@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:59:21 by azakharo          #+#    #+#             */
/*   Updated: 2024/05/26 19:27:01 by azakharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
int	main(void)
{
	char	str1[] = "";
	char	str2[] = "banana";
	char	str3[] = "apple";
	char	str4[] = "apple pie";
	char	str5[] = "apple";
	char	str6[] = "apple";

	printf("Result 1: %d\n", ft_strncmp(str1, str2, 3)); // <0
	printf("Result 2: %d\n", ft_strncmp(str1, str3, 5)); // <0
	printf("Result 3: %d\n", ft_strncmp(str4, str5, 10)); // >0
	printf("Result 4: %d\n", ft_strncmp(str5, str6, 10)); //= 0
}
*/