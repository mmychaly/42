/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:27:51 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/10 18:09:48 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_close_input(t_data *data)
{
	if (data->here_doc_pfd != -1 )
	{
		free_pipe(data->here_doc_pfd);
		close(data->here_doc_pfd);
	}
	if (data->prev_pipe != -1)
	{
		free_pipe(data->prev_pipe);
		close(data->prev_pipe);
	}
}

void	exit_total(t_data *data)
{
	exit_close_input(data);	
	if (data->cmd[data->i]->cmd_arg[1] == NULL)
	{
		write(1, "exit\n", 5);
		free_data(data);
//		free(user_input); //Si oui il faut deplacer la variable dans le structure data
//		rl_clear_history();
		exit(0);
	}
	else
	{
		if (data->cmd[data->i]->cmd_arg[2] != NULL)
		{
			write(2, "exit: too many arguments\n", 25);
			data->exit_status = 1;
			data->exit_total = 1;
			return ;
		}
	}
}