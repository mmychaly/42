/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 03:11:35 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/20 04:27:45 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_count_operation_1(t_stack *actuel_a, t_stack **stack)
{
	t_stack *max_b;
	int ra;
	int rra;
	int rb;
	int rrb;

	ra = 0;
	rra = 0;
	rb = 0;
	rrb = 0;
	ft_find_max_elem(*stack, &max_b);
	if (actuel_a->above_mid == 1)
		ra = ft_count_left_top_ra_a(actuel_a);
	else
		rra =ft_count_left_top_rra_a(actuel_a);
	if (max_b->above_mid == 1)
		rb = ft_count_left_top_rb_b(max_b);
	else
		rrb =ft_count_left_top_rrb_b(max_b);
	ft_count_total(actuel_a, ra, rra, rb, rrb);
}

void	ft_count_operation_2(t_stack *actuel_a, t_stack **stack)
{
	t_stack *under_b;
	int ra;
	int rra;
	int rb;
	int rrb;

	ra = 0;
	rra = 0;
	rb = 0;
	rrb = 0;
	ft_find_under(stack, actuel_a->nbr, &under_b);
	if (actuel_a->above_mid == 1)
		ra = ft_count_left_top_ra_a(actuel_a);
	else
		rra =ft_count_left_top_rra_a(actuel_a);
	if (under_b->above_mid == 1)
		rb = ft_count_left_top_rb_b(under_b);
	else
		rrb =ft_count_left_top_rrb_b(under_b);
	ft_count_total(actuel_a, ra, rra, rb, rrb);
}

void	ft_find_best_elem(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *actuel_a;
	
	actuel_a = *stack_a;
	ft_check_midl(stack_a);
	ft_check_midl(stack_b);
	while (actuel_a != NULL)
	{
		if(check_comp_elem(actuel_a->nbr, *stack_b) == 1)
			ft_count_operation_1(actuel_a, stack_b);
		else 
			ft_count_operation_2(actuel_a, stack_b);
		actuel_a = actuel_a->next;
	}
	ft_prepar_stack(stack_a, stack_b);
}
