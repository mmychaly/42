/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepar_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:38:38 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/20 04:28:00 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_change_position_1(t_stack *best, t_stack **stack_a, t_stack **stack_b)
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
	ft_find_max_elem(*stack_b, &max_b);
	if (best->above_mid == 1)
		ra = ft_count_left_top_ra_a(best);
	else
		rra =ft_count_left_top_rra_a(best);
	if (max_b->above_mid == 1)
		rb = ft_count_left_top_rb_b(max_b);
	else
		rrb =ft_count_left_top_rrb_b(max_b);
	ft_count_rr(stack_a, stack_b, ra, rb);
	ft_count_rrr(stack_a, stack_b, rra, rrb);
}


void	ft_change_position_2(t_stack *best, t_stack **stack_a, t_stack **stack_b)
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
	ft_find_under(stack_b, best->nbr, &under_b);
	if (best->above_mid == 1)
		ra = ft_count_left_top_ra_a(best);
	else
		rra =ft_count_left_top_rra_a(best);
	if (under_b->above_mid == 1)
		rb = ft_count_left_top_rb_b(under_b);
	else
		rrb =ft_count_left_top_rrb_b(under_b);
	ft_count_rr(stack_a, stack_b, ra, rb);
	ft_count_rrr(stack_a, stack_b, rra, rrb);
}

void	ft_prepar_stack(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *best;

	ft_check_best_elem(*stack_a, &best);
	if(check_comp_elem(best->nbr, *stack_b) == 1)
		ft_change_position_1(best, stack_a, stack_b);
	else 
		ft_change_position_2(best, stack_a, stack_b);
}
