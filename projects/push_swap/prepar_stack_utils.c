/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepar_stack_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:43:22 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/20 02:44:47 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_check_best_elem(t_stack *stack, t_stack **best)
{
		t_stack *actuel;
		t_stack *temp;

		actuel = stack;
		temp = actuel;
		while (actuel->next != NULL)
		{
			if (temp->nbr_oper > actuel->next->nbr_oper)
				temp = actuel->next;
			actuel = actuel->next;
		}
		*best = temp;
}

void	ft_count_rr(t_stack **stack_a, t_stack **stack_b, int ra, int rb)
{
	int rr;
	
	rr = 0;
	if (ra != 0 && rb != 0)
	{
		while (ra > 0 && rb > 0)
		{
			ra -= 1;
			rb -= 1;
			rr += 1;
		}
	}
	if (rr != 0)
	{
		while (rr > 0)
		{
			write(1, "rr\n", 3);
			ft_rotate_all(stack_a, stack_b);
			rr--;
		}
	}
	if (ra != 0)
	{
		while (ra > 0)
		{
			write(1, "ra\n", 3);
			ft_rotate(stack_a);
			ra--;
		}
	}
	if (rb != 0)
	{
		while (rb > 0)
		{
			write(1, "rb\n", 3);
			ft_rotate(stack_b);
			rb--;
		}
	}
}

void	ft_count_rrr(t_stack **stack_a, t_stack **stack_b, int rra, int rrb)
{
	int rrr;
	
	rrr = 0;
	if (rra != 0 && rrb != 0)
	{
		while (rra > 0 && rrb > 0)
		{
			rra -= 1;
			rrb -= 1;
			rrr += 1;
		}
	}
	if (rrr != 0)
	{
		while (rrr > 0)
		{
			write(1, "rrr\n", 4);
			ft_rev_rotate_all(stack_a, stack_b);
			rrr--;
		}
	}
	if (rra != 0)
	{
		while (rra > 0)
		{
			write(1, "rra\n", 4);
			ft_rev_rotate(stack_a);
			rra--;
		}
	}
	if (rrb != 0)
	{
		while (rrb > 0)
		{
			write(1, "rrb\n", 4);
			ft_rev_rotate(stack_b);
			rrb--;
		}
	}	
}

