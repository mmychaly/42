/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_elem_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 03:44:21 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/24 04:10:24 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_comp_elem(int nbr, t_stack *stack_b)
{
	t_stack	*actuel;

	actuel = stack_b;
	while (actuel != NULL)
	{
		if (nbr < actuel->nbr)
			break ;
		actuel = actuel->next;
	}
	if (actuel == NULL)
		return (1);
	actuel = stack_b;
	while (actuel != NULL)
	{
		if (nbr > actuel->nbr)
			break ;
		actuel = actuel->next;
	}
	if (actuel == NULL)
		return (1);
	return (0);
}

void	ft_find_max_elem(t_stack *stack, t_stack **max)
{
	t_stack	*actuel;
	t_stack	*temp;

	actuel = stack;
	temp = actuel;
	while (actuel->next != NULL)
	{
		if (temp->nbr < actuel->next->nbr)
			temp = actuel->next;
		actuel = actuel->next;
	}
	*max = temp;
}

void	ft_find_under(t_stack **stack, int nbr, t_stack **under)
{
	t_stack	*actuel;
	t_stack	*pos;

	actuel = *stack;
	pos = NULL;
	while (actuel != NULL)
	{
		if (actuel->nbr < nbr && (pos == NULL || actuel->nbr > pos->nbr))
			pos = actuel;
		actuel = actuel->next;
	}
	*under = pos;
}

int	ft_count_total(int ra, int rra, int rb, int rrb)
{
	int	total;
	int	rr;
	int	rrr;

	total = 1;
	rr = 0;
	rrr = 0;
	while (ra > 0 && rb > 0)
	{
		ra -= 1;
		rb -= 1;
		rr += 1;
	}
	while (rra > 0 && rrb > 0)
	{
		rra -= 1;
		rrb -= 1;
		rrr += 1;
	}
	total = total + ra + rra + rb + rrb + rr + rrr;
	return (total);
}
