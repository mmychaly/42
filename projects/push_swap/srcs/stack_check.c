/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:32:09 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 00:34:42 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack **stack_a, int len_a)
{
	t_stack	*max;
	t_stack	*min;

	if (ft_check_sort(*stack_a, len_a) == 0)
	{
		check_min_max(*stack_a, &min, &max);
		if (max->index + 1 == min->index)
		{
			if (min->above_mid == 0)
				ft_display_and_start_rra(stack_a);
			else
				ft_display_and_start_ra(stack_a);
		}
		else if (min->index + 1 == max->index)
			ft_display_and_start_sa(stack_a);
		else if (min->index == 2 && max->index == 0)
			ft_display_and_start_sa(stack_a);
	}
	while (ft_check_sort(*stack_a, len_a) == 0)
		ft_sort_three(stack_a, len_a);
}

void	ft_push_back(t_stack **stack_a, t_stack **stack_b, int a, int b)
{
	while (b > 0)
	{
		ft_find_pos(stack_a, (*stack_b)->nbr);
		ft_display_and_start_pa(stack_b, stack_a);
		a++;
		b--;
	}
}

void	ft_push_stack_b(t_stack **stack_a, int *a, t_stack **stack_b, int *b)
{
	int	len_a;
	int	len_b;

	len_a = *a;
	len_b = *b;
	while (len_a > 3 && len_b < 2)
	{
		ft_display_and_start_pb(stack_a, stack_b);
		len_a--;
		len_b++;
	}
	while (len_a > 3)
	{
		ft_find_best_elem(stack_a, stack_b);
		ft_display_and_start_pb(stack_a, stack_b);
		len_a--;
		len_b++;
	}
	*a = len_a;
	*b = len_b;
}

void	ft_stack_over_three(t_stack **stack_a, int a, t_stack **stack_b, int b)
{
	t_stack	*max;
	t_stack	*min;
	int		*count_a;
	int		*count_b;

	max = NULL;
	min = NULL;
	count_a = &a;
	count_b = &b;
	if (ft_check_sort(*stack_a, a) == 0)
	{
		ft_push_stack_b(stack_a, count_a, stack_b, count_b);
		a = *count_a;
		b = *count_b;
		ft_sort_three(stack_a, a);
		ft_push_back(stack_a, stack_b, a, b);
		a += b;
		b = 0;
		check_min_max(*stack_a, &min, &max);
		if (ft_check_sort(*stack_a, a) == 0)
			ft_sort_a(stack_a, min, max);
	}
}

void	ft_stack_check(t_stack **stack_a, int a, t_stack **stack_b, int b)
{
	if (ft_check_sort(*stack_a, a) == 1)
		return ;
	if (a == 1)
		return ;
	else if (a == 2)
	{
		if (ft_check_sort(*stack_a, a) == 0)
		{
			ft_display_and_start_sa(stack_a);
			return ;
		}
	}
	else if (a == 3)
	{
		ft_sort_three(stack_a, a);
		return ;
	}
	if (a > 3)
		ft_stack_over_three(stack_a, a, stack_b, b);
}
