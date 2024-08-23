/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_elem_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 03:44:21 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/20 04:21:54 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_comp_elem(int nbr, t_stack *stack_b) //Проверяю является ли число в из элемента стека а максимальным/минимальным для стека б
{
	t_stack *actuel;
	actuel = stack_b;
	while (actuel != NULL)
	{
		if (nbr < actuel->nbr)
			break;
		actuel = actuel->next;
	}
	if (actuel == NULL)
		return (1);
	actuel = stack_b;
	while (actuel != NULL)
	{
		if (nbr > actuel->nbr)
			break;
		actuel = actuel->next;
	}
	if (actuel == NULL)
		return (1);
	return (0);
}

void	ft_find_max_elem(t_stack *stack, t_stack **max)
{
		t_stack *actuel;
		t_stack *temp;

		actuel = stack;
		temp = actuel;
		while (actuel->next != NULL)
		{
			if (temp->nbr < actuel->next->nbr)
				temp = actuel->next;
			actuel = actuel->next;
		}
		*max = temp;
}
void	ft_find_under(t_stack **stack, int nbr, t_stack **under) // функция должна пройти по стеку б и найти элимент содержащий следующие меньшее число по сравнению с переданным числом
{
	t_stack *actuel;
	t_stack *pos;

	actuel = *stack;
	pos = NULL;
	while (actuel != NULL)
	{
		if (actuel->nbr < nbr && (pos == NULL || actuel->nbr > pos->nbr)) //Если текущее число меньше переданного при это pos пустой либо меньше нового числа 
			pos = actuel;
		actuel = actuel->next;
	}
	*under = pos;
}

int	ft_count_left_top_ra_a(t_stack *actual)
{
	int ra;
	
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
	int rra;

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
	int rrb;
	
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
	int rb;
	
	rb = 0;
	while (actual != NULL && actual->index != 0)
	{
		rb++;
		actual = actual->prev;
	}
	return (rb);
}

void ft_count_total(t_stack *actuel_a, int ra, int rra, int rb, int rrb)
{
	int total;
	int rr;
	int rrr;
	
	total = 1;
	rr = 0;
	rrr = 0;
	if (ra != 0 && rb != 0)
		while (ra > 0 && rb > 0)
		{
			ra -= 1;
			rb -= 1;
			rr += 1;
		}
	if (rra != 0 && rrb != 0)
		while (rra > 0 && rrb > 0)
		{
			rra -= 1;
			rrb -= 1;
			rrr += 1;
		}
	total = total + ra + rra + rb + rrb + rr + rrr;
	actuel_a->nbr_oper = total;
}

