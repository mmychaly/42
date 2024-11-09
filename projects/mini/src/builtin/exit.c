/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:27:51 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/09 18:21:50 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_func(data)

void	exit_total(t_data *data)
{
	if (data->cmd[data->i]->cmd_arg[1] == NULL)
		exit(0);
	else
	{
		if (data->cmd[data->i]->cmd_arg[2] != NULL)
		{
			write(2, "exit: too many arguments\n", );
			return ;
		}
	}
}