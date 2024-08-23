/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:39:09 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/23 17:46:37 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_sort(t_stack *stack, int len)
{
	t_stack *actuel;
	int i;
	int sort_flag;
	int middle;

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
		t_stack *actuel;
		t_stack *temp;

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

	if (!stack || !*stack )
		return;
	actuel = *stack;
	i = 0;
	while (actuel != NULL)
	{
		actuel->index = i;
		actuel = actuel->next;
		i++;
	}
}

void ft_check_midl(t_stack **stack)
{
	t_stack *actuel;
	int middle;
	int len;

	actuel = *stack;
	len = 0;
	while(actuel != NULL)
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
	t_stack *actuel;
	t_stack *pos;

	actuel = *stack_a;
	pos = NULL;
	while (actuel != NULL)
	{

		if (actuel->nbr > top_b && (pos == NULL || actuel->nbr < pos->nbr)) //Если текущее число меньше переданного при это pos пустой либо меньше нового числа 
			pos = actuel;
		actuel = actuel->next;
	}
	if (pos == NULL)
		return;
	actuel = *stack_a;
	while (pos->index != 0)
	{
		if (pos->above_mid == 1)
		{
			write(1, "ra\n", 3);
			ft_rotate(stack_a);
		}
		else
		{
			write(1, "rra\n", 4);
			ft_rev_rotate(stack_a);
		}
		ft_check_midl(stack_a);
	}
}

void ft_sort_a(t_stack **stack_a, t_stack *min, t_stack *max)
{
	check_min_max(*stack_a, &min, &max);
	while (min->index != 0)
	{
		if (min->above_mid == 1)
		{
			write(1, "ra\n", 3);
			ft_rotate(stack_a);
		}
		else
		{
			write(1, "rra\n", 4);
			ft_rev_rotate(stack_a);
		}
	}
}

void ft_sort_b(t_stack **stack_b, t_stack *min, t_stack *max)
{
	check_min_max(*stack_b, &min, &max);
	while (max->index != 0)
	{
		if (max->above_mid == 1)
		{
			write(1, "rb\n", 3);
			ft_rotate(stack_b);
		}
		else
		{
			write(1, "rrb\n", 4);
			ft_rev_rotate(stack_b);
		}
	}
}
