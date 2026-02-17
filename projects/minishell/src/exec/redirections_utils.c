/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 06:14:18 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/04 02:44:44 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	manage_fd_redirection_input(t_data *data, int flag_heredoc)
{
	if (data->i != 0)
	{
		if (check_cmd(data) == 0)
			free_pipe(data->cmd[data->i - 1]->prev_pipe);
		close(data->cmd[data->i - 1]->prev_pipe);
		data->cmd[data->i - 1]->prev_pipe = 0;
	}
	if (flag_heredoc == 1)
	{
		if (data->cmd[data->i]->here_doc_pfd != 0)
		{
			free_pipe(data->cmd[data->i]->here_doc_pfd);
			close(data->cmd[data->i]->here_doc_pfd);
			data->cmd[data->i]->here_doc_pfd = 0;
		}
	}
	if (data->i != data->nb_pipe)
		close(data->pipefd[0]);
}

int	check_input_files(t_data *data, int flag_heredoc)
{
	int	i;
	int	fd_in;

	i = 0;
	if (data->cmd[data->i]->input_file != NULL)
	{
		while (data->cmd[data->i]->input_files[i] != NULL)
		{
			fd_in = open(data->cmd[data->i]->input_files[i], O_RDONLY, 0644);
			if (fd_in == -1)
			{
				perror("Error opening input file");
				if (flag_heredoc == 1)
					close_here_doc_pfd(data->cmd[data->i]->here_doc_pfd);
				if (data->i != data->nb_pipe)
					close(data->pipefd[1]);
				if (exit_cmds_builtin(data, NULL, 1, NULL) == 1)
					return (1);
			}
			close(fd_in);
			i++;
		}
	}
	return (0);
}

void	redirection_input_stdin(t_data *data, int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Error duplicating file descriptor for input");
		if (data->i != data->nb_pipe)
			close(data->pipefd[1]);
		close(fd_in);
		close_other_fd(data);
		close_prev_pipes_in_child(data);
		free_all_data(data);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

void	redirection_here_doc_stdin(t_data *data)
{
	if (dup2(data->cmd[data->i]->here_doc_pfd, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 prev_pipe");
		free_pipe(data->cmd[data->i]->here_doc_pfd);
		close(data->cmd[data->i]->here_doc_pfd);
		data->cmd[data->i]->here_doc_pfd = 0;
		if (data->i != data->nb_pipe)
			close(data->pipefd[1]);
		close_other_fd(data);
		close_prev_pipes_in_child(data);
		free_all_data(data);
		rl_clear_history();
		exit (EXIT_FAILURE);
	}
}

void	manage_fd_redirection_output(t_data *data)
{
	if (data->nb_pipe == 0 && data->builtin_cmd
		== 1 && data->display_builtin_cmd == 1)
		data->std_out = dup(1);
	if (data->i != data->nb_pipe)
	{
		close(data->pipefd[1]);
	}
}
