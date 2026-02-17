/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 01:36:08 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/04 03:37:06 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_other_fd(t_data *data)
{
	int	i_2;

	i_2 = 0;
	while (data->cmd[i_2] != NULL)
	{
		if (data->cmd[i_2]->here_doc_pfd != 0)
			close(data->cmd[i_2]->here_doc_pfd);
		i_2++;
	}
}

void	close_prev_pipes_in_child(t_data *data)
{
	int	i_2;

	i_2 = 0;
	while (data->cmd[i_2] != NULL)
	{
		if (data->cmd[i_2]->prev_pipe != 0)
		{
			close(data->cmd[i_2]->prev_pipe);
			data->cmd[i_2]->prev_pipe = 0;
		}
		i_2++;
	}
}

void	close_prev_pipes_in_parent(t_data *data)
{
	int	i_2;

	i_2 = 0;
	while (data->cmd[i_2] != NULL)
	{
		if (data->cmd[i_2]->prev_pipe != 0)
		{
			free_pipe(data->cmd[i_2]->prev_pipe);
			close(data->cmd[i_2]->prev_pipe);
			data->cmd[i_2]->prev_pipe = 0;
		}
		i_2++;
	}
}

void	check_path(t_data *data)
{
	int	i;

	i = 0;
	while (ft_strnstr(data->envp[i], "PATH", 4) == 0)
	{
		i++;
		if (data->envp[i] == NULL)
		{
			write(2, "ERROR: don't find PATH\n", 23);
			if (data->nb_pipe == 0 && data->builtin_cmd == 1)
			{
				data->exit_status = 127;
				if (data->cmd[0]->here_doc_pfd != 0)
					free_pipe(data->cmd[0]->here_doc_pfd);
				data->back_in_main = 1;
				return ;
			}
			else
			{
				if (data->flag_pipe > 0)
					free_pipe(0);
				free_child(data, 127);
			}
		}
	}
}
