/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 01:32:33 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 00:34:20 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_a(t_stack **stack_a, t_stack *min, t_stack *max)
{
	check_min_max(*stack_a, &min, &max);
	while (min->index != 0)
	{
		if (min->above_mid == 1)
			ft_display_and_start_ra(stack_a);
		else
			ft_display_and_start_rra(stack_a);
	}
}

void	check_bigger_in_a(t_stack *actuel, t_stack **pos, int top_b)
{
	while (actuel != NULL)
	{
		if (actuel->nbr > top_b && ((*pos) == NULL
				|| actuel->nbr < (*pos)->nbr))
			*pos = actuel;
		actuel = actuel->next;
	}
}
