/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:39:09 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 00:29:44 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	check_min_max(t_stack *stack_a, t_stack **min, t_stack **max)
{
	t_stack	*actuel;
	t_stack	*temp;

	actuel = stack_a;
	temp = actuel;
	while (actuel->next != NULL)
	{
		if (temp->nbr > actuel->next->nbr)
			temp = actuel->next;
		actuel = actuel->next;
	}
	*min = temp;
	actuel = stack_a;
	temp = actuel;
	while (actuel->next != NULL)
	{
		if (temp->nbr < actuel->next->nbr)
			temp = actuel->next;
		actuel = actuel->next;
	}
	*max = temp;
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

void	ft_check_midl(t_stack **stack)
{
	t_stack	*actuel;
	int		middle;
	int		len;

	actuel = *stack;
	len = 0;
	while (actuel != NULL)
	{
		len++;
		actuel = actuel->next;
	}
	middle = len / 2;
	actuel = *stack;
	while (actuel != NULL)
	{
		if (actuel->index <= middle)
			actuel->above_mid = 1;
		else
			actuel->above_mid = 0;
		actuel = actuel->next;
	}
}

void	ft_find_pos(t_stack **stack_a, int top_b)
{
	t_stack	*actuel;
	t_stack	*pos;
	t_stack	*max;
	t_stack	*min;

	actuel = *stack_a;
	pos = NULL;
	max = NULL;
	min = NULL;
	check_min_max(*stack_a, &min, &max);
	if (top_b > max->nbr)
		pos = min;
	else
		check_bigger_in_a(actuel, &pos, top_b);
	while (pos->index != 0)
	{
		if (pos->above_mid == 1)
			ft_display_and_start_ra(stack_a);
		else
			ft_display_and_start_rra(stack_a);
		ft_check_midl(stack_a);
	}
}
