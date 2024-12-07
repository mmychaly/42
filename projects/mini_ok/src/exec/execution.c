/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:06:33 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/04 02:52:31 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_launch_cmd(t_data *data)
{
	char	*cmd;

	signal(SIGQUIT, sig_upd);
	redirection(data);
	execute_builtin_command(data);
	if (data->cmd[data->i]->cmd == NULL)
		exit_only_child(data, 0);
	check_file_args(data);
	if (data->cmd[data->i]->cmd[0] == '\0')
		error_empty_cmd(data);
	if (access(data->cmd[data->i]->cmd, F_OK | X_OK) == 0)
		cmd = ft_strdup(data->cmd[data->i]->cmd);
	else
		cmd = ft_envp_cherch(data->cmd[data->i]->cmd, data->envp, data);
	if (cmd == NULL)
		free_error_cmd(data);
	check_dir(data, cmd);
	close_other_fd(data);
	close_prev_pipes_in_child(data);
	if (execve(cmd, data->cmd[data->i]->cmd_arg, data->envp) == -1)
		free_fault_execve(cmd, data);
}

void	sig_upd(int sig)
{
	g_sig = sig;
}

void	child_handler(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	exit(130);
}

void	execution_cmd(t_data *data)
{
	int	pid;

	while (data->i <= data->nb_pipe)
	{
		signal(SIGINT, sig_upd);
		if (data->i != data->nb_pipe && pipe(data->pipefd) == -1)
		{
			write(2, "ERROR: pipe\n", 12);
			data->exit_status = 1;
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			error_fork(data);
			return ;
		}
		if (pid == 0)
			ft_launch_cmd(data);
		manage_fd(data, pid);
		data->i++;
	}
	wait_processes(data);
}

void	choice_execution(t_data *data)
{
	data->i = 0;
	data->flag_pipe = 0;
	if (data->nb_pipe == 0)
	{
		execute_builtin_command(data);
		if (data->back_in_main == 1)
			return ;
	}
	execution_cmd(data);
}
