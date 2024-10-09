/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:53 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/09 22:14:44 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirection_out(char *argv, t_data *data, int flag)
{
	int	fd_out;

	if (flag == 1)
		fd_out = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		error_open_outfile(data->prev_pipe);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_out");
		free_pipe(data->prev_pipe);
		close(data->prev_pipe);
		close(fd_out);
		exit (EXIT_FAILURE);
	}
	close(fd_out);
	if (dup2(data->prev_pipe, STDIN_FILENO) == -1)
		error_dup2_out(data->prev_pipe);
	close(data->prev_pipe);
}

void	ft_launch_child_2(t_data *data)
{
	char	**strs_argv;
	char	*cmd;

	data->flag = 0;
	if ((ft_strncmp(data->argv[1], "here_doc", ft_strlen(data->argv[1]))) == 0)
		data->flag = 1;
	ft_redirection_out(data->argv[data->i + 1], data, data->flag);
	if (data->argv[data->i][0] == '\0')
		error_empty_cmd();
	strs_argv = ft_split(data->argv[data->i], ' ');
	if (strs_argv == NULL)
		error_split();
	strs_argv = check_strs(strs_argv, data);
	if (strs_argv == NULL)
		error_cmd();
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = ft_strdup(strs_argv[0]);
	else
		cmd = ft_envp_cherch(strs_argv[0], data->envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv);
	if (execve(cmd, strs_argv, data->envp) == -1)
		free_fault_execve(strs_argv, cmd);
}
