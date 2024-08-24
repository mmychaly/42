/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:10:38 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/24 04:44:23 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_display_and_start_rb(t_stack **stack_b)
{
	write(1, "rb\n", 3);
	ft_rotate(stack_b);
}

void	ft_display_and_start_rrb(t_stack **stack_b)
{
	write(1, "rrb\n", 4);
	ft_rev_rotate(stack_b);
}

void	ft_display_and_start_pa(t_stack **stack_b, t_stack **stack_a)
{
	write(1, "pa\n", 3);
	ft_push(stack_b, stack_a);
}

void	ft_display_and_start_pb(t_stack **stack_a, t_stack **stack_b)
{
	write(1, "pb\n", 3);
	ft_push(stack_a, stack_b);
}
