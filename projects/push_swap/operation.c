/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:48:38 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/20 04:19:04 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_stack **stack)
{
	t_stack	*temp_next;
	t_stack	*temp_prev;

	if (!stack || !*stack || !(*stack)->next)
		ft_error_lstclear(stack);
	(*stack)->index = 1;
	(*stack)->next->index = 0;
	temp_next = (*stack)->next;
	temp_prev = (*stack)->prev;
	(*stack)->next = (*stack)->next->next;
	temp_next->next = *stack;
	*stack = temp_next;
	(*stack)->prev = temp_prev;
	(*stack)->next->prev = *stack;
	if ((*stack)->next->next != NULL)
		(*stack)->next->next->prev = (*stack)->next;
}

void	ft_rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*seconde;
	t_stack	*last;
	t_stack	*actuel;
	int		i;

	if (!stack || !*stack || !(*stack)->next)
		ft_error_lstclear(stack);
	first = *stack;
	seconde = (*stack)->next;
	last = ft_lstlast_mod(*stack);
	i = 0;
	last->next = first;
	first->next = NULL;
	seconde->prev = first->prev;
	first->prev = last;
	*stack = seconde;
	actuel = *stack;
	while (actuel != NULL)
	{
		actuel->index = i;
		actuel = actuel->next;
		i++;
	}
}

void	ft_rev_rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;
	t_stack	*seconde_last;
	t_stack	*actuel;
	int		i;

	if (!stack || !*stack || !(*stack)->next)
		ft_error_lstclear(stack);
	first = *stack;
	last = ft_lstlast_mod(*stack);
	seconde_last = last->prev;
	i = 0;
	seconde_last->next = NULL;
	last->prev = NULL;
	last->next = first;
	first->prev = last;
	*stack = last;
	actuel = *stack;
	while (actuel != NULL)
	{
		actuel->index = i;
		actuel = actuel->next;
		i++;
	}
}

void	ft_push(t_stack **stack_src, t_stack **stack_dest)
{
	t_stack	*first_src;
	t_stack	*seconde_src;

	first_src = *stack_src;
	seconde_src = (*stack_src)->next;
	if (*stack_dest == NULL)
	{
		seconde_src->prev = NULL;
		*stack_src = seconde_src;
		*stack_dest = first_src;
		first_src->next = NULL;
	}
	else
	{
		first_src->next = *stack_dest;
		first_src->next->prev = first_src;
		*stack_dest = first_src;
		if (seconde_src != NULL)
		{
			seconde_src->prev = NULL;
			*stack_src = seconde_src;
		}
		else
			*stack_src = NULL;
	}
	check_index(stack_src);
	check_index(stack_dest);
}

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
