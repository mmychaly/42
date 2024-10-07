/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 04:26:11 by mikerf            #+#    #+#             */
/*   Updated: 2024/06/03 13:49:04 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*temp;

	i = 0;
	if (nmemb != 0 && size > (((size_t) - 1) / nmemb))
		return (NULL);
	temp = malloc(size * nmemb);
	if (temp == NULL)
		return (NULL);
	while (i < (size * nmemb))
	{
		*((unsigned char *)temp + i) = 0;
		i++;
	}
	return (temp);
}
