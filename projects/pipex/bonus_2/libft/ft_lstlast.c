/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 03:24:19 by mikerf            #+#    #+#             */
/*   Updated: 2024/05/28 09:34:55 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*actuel;

	if (lst == NULL)
		return (NULL);
	actuel = lst;
	while (actuel->next != NULL)
	{
		actuel = actuel->next;
	}
	return (actuel);
}
