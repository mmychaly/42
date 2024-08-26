/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 04:14:31 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 04:22:04 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

t_stack	*ft_lstnew_mod(int data)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->nbr = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_mod(t_stack **lst, t_stack *new)
{
	t_stack	*actuel;

	actuel = *lst;
	if (lst == NULL || new == NULL)
		return ;
	if (actuel != NULL)
	{
		actuel = ft_lstlast_mod(*lst);
		new->prev = actuel;
		actuel->next = new;
	}
	else
		*lst = new;
}

t_stack	*ft_lstlast_mod(t_stack *lst)
{
	t_stack	*actuel;

	if (lst == NULL)
		return (NULL);
	actuel = lst;
	while (actuel->next != NULL)
	{
		actuel = actuel->next;
	}
	return (actuel);
}

void	ft_lstclear_mod(t_stack **lst)
{
	t_stack	*set_free;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		set_free = *lst;
		*lst = (*lst)->next;
		free(set_free);
	}
	*lst = NULL;
}

void	ft_error_lstclear(t_stack **lst)
{
	t_stack	*set_free;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		set_free = *lst;
		*lst = (*lst)->next;
		free(set_free);
	}
	*lst = NULL;
	write(2, "Error\n", 6);
	exit(1);
}
