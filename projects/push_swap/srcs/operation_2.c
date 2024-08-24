/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:53:56 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/23 22:08:36 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_all(t_stack **stack_a, t_stack **stack_b)
{
	ft_rotate(stack_a);
	ft_rotate(stack_b);
}

void	ft_rev_rotate_all(t_stack **stack_a, t_stack **stack_b)
{
	ft_rev_rotate(stack_a);
	ft_rev_rotate(stack_b);
}

void	ft_display_and_start_sa(t_stack **stack_a)
{
	write(1, "sa\n", 3);
	ft_swap(stack_a);
}

void	ft_display_and_start_ra(t_stack **stack_a)
{
	write(1, "ra\n", 3);
	ft_rotate(stack_a);
}

void	ft_display_and_start_rra(t_stack **stack_a)
{
	write(1, "rra\n", 4);
	ft_rev_rotate(stack_a);
}
