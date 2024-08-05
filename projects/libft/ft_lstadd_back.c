/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:56 by mikerf            #+#    #+#             */
/*   Updated: 2024/05/28 09:39:46 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*actuel;

	actuel = *lst;
	if (lst == NULL || new == NULL)
		return ;
	if (actuel != NULL)
	{
		actuel = ft_lstlast(*lst);
		actuel->next = new;
	}
	else
		*lst = new;
}
