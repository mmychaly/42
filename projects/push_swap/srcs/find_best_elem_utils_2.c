/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_elem_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 04:01:35 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/24 04:12:09 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_count_left_top_ra_a(t_stack *actual)
{
	int	ra;

	ra = 0;
	while (actual != NULL && actual->index != 0)
	{
		ra++;
		actual = actual->prev;
	}
	return (ra);
}

int	ft_count_left_top_rra_a(t_stack *actual)
{
	int	rra;

	rra = 0;
	while (actual != NULL && actual->index != 0)
	{
		rra++;
		actual = actual->next;
	}
	return (rra);
}

int	ft_count_left_top_rrb_b(t_stack *actual)
{
	int	rrb;

	rrb = 0;
	while (actual != NULL && actual->index != 0)
	{
		rrb++;
		actual = actual->next;
	}
	return (rrb);
}

int	ft_count_left_top_rb_b(t_stack *actual)
{
	int	rb;

	rb = 0;
	while (actual != NULL && actual->index != 0)
	{
		rb++;
		actual = actual->prev;
	}
	return (rb);
}
