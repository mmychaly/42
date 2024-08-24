/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 02:00:47 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/25 01:30:11 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
