/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:00:47 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/26 03:09:40 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	ft_error_exit(int nbr)
{
	write(2, "Error\n", 6);
	if (nbr == 1)
		exit(EXIT_FAILURE);
	else
		exit(nbr);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	ft_free_error_exit(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	free_all_exit(char *str, t_stack **stack_a, t_stack **stack_b)
{
	write(2, "Error\n", 6);
	free(str);
	ft_lstclear_mod(stack_b);
	ft_lstclear_mod(stack_a);
	str = get_next_line(0);
	while (str != NULL)
	{
		free(str);
		str = get_next_line(0);
	}
	exit(5);
}
