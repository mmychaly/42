/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chek.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 03:48:11 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/31 14:47:43 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_check_digit(char **strs)
{
	int	i;
	int	i_2;

	i = 0;
	while (strs[i] != NULL)
	{
		i_2 = 0;
		if (strs[i][0] == '-' || strs[i][0] == '+')
			i_2++;
		if (ft_isdigit(strs[i][i_2]) == 0) //J'ai ajoute pour eviter le probleme de 1 + 5 9 7 //les symbols +- sans un digit juste apres
		{
			ft_free_strs(strs);
			ft_error_exit(1);
		}	
		while (strs[i][i_2] != '\0')
		{
			if (ft_isdigit(strs[i][i_2]) == 0)
			{
				ft_free_strs(strs);
				ft_error_exit(1);
			}
			i_2++;
		}
		i++;
	}
}

void	ft_chek_double(int *array, int len_stack)
{
	int	i;
	int	i_2;

	i = 0;
	while (i < len_stack)
	{
		i_2 = i + 1;
		while (i_2 < len_stack)
		{
			if (array[i] == array[i_2])
			{
				free(array);
				ft_error_exit(1);
			}
			i_2++;
		}
		i++;
	}
}
