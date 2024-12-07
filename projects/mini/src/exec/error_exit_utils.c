/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:08:02 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/03 06:16:26 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_fault_execve(char *cmd, t_data *data)
{
	free(cmd);
	cmd = NULL;
	if (data->flag_pipe > 0)
		free_pipe(0);
	free_all_data(data);
	rl_clear_history();
	perror("ERROR execve");
	exit(126);
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

void	free_pipe(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	error_fork(t_data *data)
{
	write(2, "ERROR: fork\n", 12);
	close(data->pipefd[1]);
	close(data->pipefd[0]);
	data->exit_status = 1;
}

void	manage_fd(t_data *data, int pid)
{
	if (data->cmd[data->i]->here_doc_pfd != 0)
	{
		close(data->cmd[data->i]->here_doc_pfd);
		data->cmd[data->i]->here_doc_pfd = 0;
	}
	data->flag_pipe = 0;
	if (data->prev_pipe != -1)
		close(data->prev_pipe);
	if (data->i != data->nb_pipe)
		close(data->pipefd[1]);
	if (data->i == data->nb_pipe)
		data->prev_pipe = pid;
	else
		data->prev_pipe = data->pipefd[0];
}
