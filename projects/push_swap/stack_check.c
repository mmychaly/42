/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:32:09 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/23 17:47:15 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort_three(t_stack **stack_a, int len_a)
{
	t_stack *max;
	t_stack *min;
	
	if (ft_check_sort(*stack_a, len_a) == 0)
	{
		check_min_max(*stack_a, &min, &max);
		if (max->index + 1 == min->index)
		{
			if (min->above_mid == 0)
			{
				write(1, "rra\n", 4);
				ft_rev_rotate(stack_a);
			}
			else
			{
				write(1, "ra\n", 3);
				ft_rotate(stack_a);
			}
			}
		else if (min->index + 1 == max->index)
		{
			write(1, "sa\n", 3);
			ft_swap(stack_a);
		}
		else if (min->index == 2 && max->index == 0)
		{
			write(1, "sa\n", 3);
			ft_swap(stack_a);
		}
//			ft_stack_check(stack_a, len_a, stack_b, len_b); //Зачем?
	}
}

void	ft_push_back(t_stack **stack_a, t_stack **stack_b, int len_a, int len_b)
{
	while (len_b > 0)
	{
		ft_find_pos(stack_a, (*stack_b)->nbr);
		write(1, "pa\n", 3);
		ft_push(stack_b, stack_a);
		len_a++;
		len_b--;
	}
}
/*
void	ft_stack_check(t_stack **stack_a, int len_a, t_stack **stack_b, int	len_b)
{
	t_stack *max;
	t_stack *min;
	t_stack *actuel;
	
	if (ft_check_sort(*stack_a, len_a) == 1)
		return ;
	if (len_a == 1)
	{
		ft_lstclear_mod(stack_a);	
		exit(0);
	}
	else if (len_a == 2)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			write(1, "sa\n", 3);
			ft_swap(stack_a);
			return ;
		}
	}
	else if (len_a == 3)
	{
		ft_sort_three(stack_a, len_a);
		check_min_max(*stack_a, &min, &max);
		ft_push_back(stack_a, stack_b, len_a, len_b);
		if (ft_check_sort(*stack_a, len_a) == 0)
			ft_sort_a(stack_a, min, max);
		actuel = *stack_a;
		printf("after final sort\n");
		printf("len_a == %i  len_b == %i\n", len_a, len_b);
		while (actuel != NULL)
		{
			printf("stack a index == %i // nomber == %i\n", actuel->index, actuel->nbr);
			actuel = actuel->next;
		}
		printf("*************************\n");
		if (len_a > 3)
			return ;
	}
	if	(len_a > 3)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			while (len_a > 3 && len_b < 2)
			{
				write(1, "pb\n", 3);
				ft_push(stack_a, stack_b);
				len_a--;
				len_b++;
			}
			while (len_a > 3)
			{
				ft_find_best_elem(stack_a, stack_b);
				write(1, "pb\n", 3);
				ft_push(stack_a, stack_b);
				len_a--;
				len_b++;
			}
			ft_sort_b(stack_b, min, max);
			ft_sort_three(stack_a, len_a);
			ft_stack_check(stack_a, len_a, stack_b, len_b); //Зачем?
		}
	}
}*/


void	ft_stack_check(t_stack **stack_a, int len_a, t_stack **stack_b, int	len_b)
{
	t_stack *max;
	t_stack *min;
//	t_stack *actual;

	max = NULL;
	min = NULL;
	if (ft_check_sort(*stack_a, len_a) == 1)
		return ;
	if (len_a == 1)
	{
		ft_lstclear_mod(stack_a);	
		exit(0);
	}
	else if (len_a == 2)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			write(1, "sa\n", 3);
			ft_swap(stack_a);
			return ;
		}
	}
	else if (len_a == 3)
	{
		ft_sort_three(stack_a, len_a);
		return ;
	}
	if	(len_a > 3)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			while (len_a > 3 && len_b < 2)
			{
				write(1, "pb\n", 3);
				ft_push(stack_a, stack_b);
				len_a--;
				len_b++;
			}
			while (len_a > 3)
			{
				ft_find_best_elem(stack_a, stack_b);
				write(1, "pb\n", 3);
				ft_push(stack_a, stack_b);
				len_a--;
				len_b++;
			}
			ft_sort_b(stack_b, min, max);
			ft_sort_three(stack_a, len_a);
			ft_sort_a(stack_a, min, max);
			ft_push_back(stack_a, stack_b, len_a, len_b);
			len_a += len_b;
			len_b = 0; 
			check_min_max(*stack_a, &min, &max);
			if (ft_check_sort(*stack_a, len_a) == 0)
				ft_sort_a(stack_a, min, max);
/*			actual = *stack_a;
			while (actual != NULL)
			{
				printf("in ft_rotate index == %i // nomber == %i\n", actual->index, actual->nbr);
				actual = actual->next;
			}*/
		}
	}
}

/*Вывести список
	actuel = *stack;
	while (actuel != NULL)
	{
		printf("in ft_rotate index == %i // nomber == %i\n", actuel->index, actuel->nbr);
		actuel = actuel->next;
	}
*/

/*
void	ft_stack_check(t_stack **stack_a, int len_a, t_stack **stack_b, int	len_b)
{
	t_stack *max;
	t_stack *min;
	t_stack *actuel;
	
	if (ft_check_sort(*stack_a, len_a) == 1)
		return ;
	if (len_a == 1)
	{
		ft_lstclear_mod(stack_a);	
		exit(0);
	}
	else if (len_a == 2)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			write(1, "sa\n", 3);
			ft_swap(stack_a);
			return ;
		}
	}
	else if (len_a == 3)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			check_min_max(*stack_a, &min, &max);
			if (max->index + 1 == min->index)
			{
				if (min->above_mid == 0)
				{
					write(1, "rra\n", 4);
					ft_rev_rotate(stack_a);
				}
				else
				{
					write(1, "ra\n", 3);
					ft_rotate(stack_a);
				}
			}
			else if (min->index + 1 == max->index)
			{
				write(1, "sa\n", 3);
				ft_swap(stack_a);
			}
			else if (min->index == 2 && max->index == 0)
			{
				write(1, "sa\n", 3);
				ft_swap(stack_a);
			}
			ft_stack_check(stack_a, len_a, stack_b, len_b); //Зачем?
		}
		while (len_b > 0)
		{
			ft_find_pos(stack_a, (*stack_b)->nbr);
			write(1, "pa\n", 3);
			ft_push(stack_b, stack_a);
			len_a++;
			len_b--;
		}
		if (ft_check_sort(*stack_a, len_a) == 0)
			ft_sort_a(stack_a, min, max);
		actuel = *stack_a;
		printf("after final sort\n");
		printf("len_a == %i  len_b == %i\n", len_a, len_b);
		while (actuel != NULL)
		{
			printf("stack a index == %i // nomber == %i\n", actuel->index, actuel->nbr);
			actuel = actuel->next;
		}
		printf("*************************\n");
		if (len_a > 3)
			return ;
	}
	if	(len_a > 3)
	{
		if (ft_check_sort(*stack_a, len_a) == 0)
		{
			while (len_a > 3 && len_b < 2)
			{
				write(1, "pb\n", 3);
				ft_push(stack_a, stack_b);
				len_a--;
				len_b++;
			}
			while (len_a > 3)
			{
				ft_find_best_elem(stack_a, stack_b);
				write(1, "pb\n", 3);
				ft_push(stack_a, stack_b);
				len_a--;
				len_b++;
			}
			ft_sort_b(stack_b, min, max);
			ft_stack_check(stack_a, len_a, stack_b, len_b); //Зачем?
		}
	}
}
*/