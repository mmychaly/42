/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepar_stack_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 04:37:31 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/26 00:01:40 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_display_launch_last_ra(t_stack **stack_a, int ra)
{
	write(1, "ra\n", 3);
	ft_rotate(stack_a);
	ra--;
	return (ra);
}

int	ft_display_launch_last_rb(t_stack **stack_b, int rb)
{
	write(1, "rb\n", 3);
	ft_rotate(stack_b);
	rb--;
	return (rb);
}

int	ft_display_launch_last_rrr(t_stack **stk_a, t_stack **stk_b, int rrr)
{
	write(1, "rrr\n", 4);
	ft_rev_rotate_all(stk_a, stk_b);
	rrr--;
	return (rrr);
}

int	ft_display_launch_last_rra(t_stack **stack_a, int rra)
{
	write(1, "rra\n", 4);
	ft_rev_rotate(stack_a);
	rra--;
	return (rra);
}

int	ft_display_launch_last_rrb(t_stack **stack_b, int rrb)
{
	write(1, "rrb\n", 4);
	ft_rev_rotate(stack_b);
	rrb--;
	return (rrb);
}
