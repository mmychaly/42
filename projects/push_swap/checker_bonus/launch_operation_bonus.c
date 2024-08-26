/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_operation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 02:44:44 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/26 03:05:58 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	ft_launch_s(char *str, int len, t_stack **stack_a, t_stack **stack_b)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(str, "sa\n", len) == 0)
	{
		ft_swap(stack_a);
		flag = 1;
	}
	else if (ft_strncmp(str, "sb\n", len) == 0)
	{
		ft_swap(stack_b);
		flag = 1;
	}
	else if (ft_strncmp(str, "ss\n", len) == 0)
	{
		ft_swap_all(stack_a, stack_b);
		flag = 1;
	}
	return (flag);
}

int	ft_launch_r(char *str, int len, t_stack **stack_a, t_stack **stack_b)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(str, "ra\n", len) == 0)
	{
		ft_rotate(stack_a);
		flag = 1;
	}
	else if (ft_strncmp(str, "rb\n", len) == 0)
	{
		ft_rotate(stack_b);
		flag = 1;
	}
	else if (ft_strncmp(str, "rr\n", len) == 0)
	{
		ft_rotate_all(stack_a, stack_b);
		flag = 1;
	}
	return (flag);
}

int	ft_launch_rrr(char *str, int len, t_stack **stack_a, t_stack **stack_b)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(str, "rra\n", len) == 0)
	{
		ft_rev_rotate(stack_a);
		flag = 1;
	}
	else if (ft_strncmp(str, "rrb\n", len) == 0)
	{
		ft_rev_rotate(stack_b);
		flag = 1;
	}
	else if (ft_strncmp(str, "rrr\n", len) == 0)
	{
		ft_rev_rotate_all(stack_a, stack_b);
		flag = 1;
	}
	return (flag);
}

int	ft_launch_p(char *str, int len, t_stack **stack_a, t_stack **stack_b)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(str, "pa\n", len) == 0)
	{
		ft_push(stack_b, stack_a);
		flag = 1;
	}
	else if (ft_strncmp(str, "pb\n", len) == 0)
	{
		ft_push(stack_a, stack_b);
		flag = 1;
	}
	return (flag);
}
