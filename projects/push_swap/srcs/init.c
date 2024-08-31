/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:23:11 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/31 11:54:55 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	**ft_manual_split(int argc, char **argv)
{
	int		i;
	char	**strs;
	char	*temp;

	i = 1;
	strs = NULL;
	strs = malloc(sizeof(char *) * argc);
	if (strs == NULL)
		ft_error_exit(1);
	strs[argc - 1] = NULL;
	while (i < argc)
	{
		temp = ft_strdup(argv[i]);
		if (temp == NULL)
		{
			ft_free_strs(strs);
			ft_error_exit(1);
		}
		strs[i - 1] = temp;
		i++;
	}
	return (strs);
}

int	ft_atoi_mod(const char *nptr, char **strs, int *array)
{
	int		i;
	int		negativ;
	long	result;

	i = 0;
	negativ = 1;
	result = 0;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negativ *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	result = result * negativ;
	if (result < INT_MIN || result > INT_MAX)
	{
		free(array);
		ft_free_error_exit(strs);
	}
	return ((int)result);
}

int	*ft_creat_int_array(char **strs, int len_stack)
{
	int		*array;
	int		i;

	i = 0;
	array = malloc(sizeof(int) * len_stack);
	if (array == NULL)
		ft_free_error_exit(strs);
	while (i < len_stack)
	{
		array[i] = ft_atoi_mod(strs[i], strs, array);
		i++;
	}
	ft_free_strs(strs);
	return (array);
}

void	ft_creat_stack(t_stack **stack, int *array, int len_stack)
{
	t_stack	*new;
	int		i;

	new = NULL;
	i = 0;
	*stack = ft_lstnew_mod(array[i]);
	if (stack == NULL)
	{
		free(array);
		ft_error_exit(1);
	}
	i++;
	while (i < len_stack)
	{
		new = ft_lstnew_mod(array[i]);
		if (new == NULL)
		{
			free(array);
			ft_lstclear_mod(stack);
			ft_error_exit(1);
		}
		ft_lstadd_back_mod(stack, new);
		i++;
	}
	free(array);
}

void	ft_init(t_stack **stack, int argc, char *argv[])
{
	t_stack	*stack_b;
	char	**temp_stack;
	int		*array;
	int		len_stack;
	int		len_b;

	temp_stack = NULL;
	stack_b = NULL;
	len_stack = 0;
	len_b = 0;
	if (argc == 2)
		temp_stack = ft_split(argv[1], ' ');
	else
		temp_stack = ft_manual_split(argc, argv);
	if (temp_stack == NULL)
		ft_error_exit(1);
	while (temp_stack[len_stack] != NULL)
		len_stack++;
	ft_check_digit(temp_stack);
	array = ft_creat_int_array(temp_stack, len_stack);
	ft_chek_double(array, len_stack);
	ft_creat_stack(stack, array, len_stack);
	ft_stack_check(stack, len_stack, &stack_b, len_b);
}
