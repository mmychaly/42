/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:39:09 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 04:32:52 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	ft_check_sort(t_stack *stack, int len)
{
	t_stack	*actuel;
	int		i;
	int		sort_flag;
	int		middle;

	actuel = stack;
	i = 0;
	middle = len / 2;
	sort_flag = 1;
	while (actuel != NULL)
	{
		actuel->index = i;
		if (i <= middle)
			actuel->above_mid = 1;
		else
			actuel->above_mid = 0;
		if (actuel->next != NULL && actuel->nbr > actuel->next->nbr)
			sort_flag = 0;
		actuel = actuel->next;
		i++;
	}
	return (sort_flag);
}

void	check_index(t_stack **stack)
{
	t_stack	*actuel;
	int		i;

	if (!stack || !*stack)
		return ;
	actuel = *stack;
	i = 0;
	while (actuel != NULL)
	{
		actuel->index = i;
		actuel = actuel->next;
		i++;
	}
}
