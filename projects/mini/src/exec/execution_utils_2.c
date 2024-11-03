/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 04:19:01 by mmychaly          #+#    #+#             */
/*   Updated: 2024/11/03 17:50:41 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_sigint(int sig) 
{
	(void) sig;
	if (g_pid == -1) 
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_pid == -5)
	{
		write(1, "\n", 1);
		g_pid = -10;
	}
	else if (g_pid > 0)
	{
		write(1, "\n", 2);
		kill(g_pid, SIGINT);
		g_pid = -100;
	}
}

void	wait_processes(t_data *data)
{
	int	pid;
	int	status;
	int signal;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->prev_pipe) //Здесь я неуверен
		{
			if (WIFEXITED(status))
				data->exit_status = (WEXITSTATUS(status));
			else if (WIFSIGNALED(status)) 
			{
				signal = WTERMSIG(status);
				data->exit_status = 128 + signal;
				if (data->exit_status == 131) //Условие треубется для того что бы корректно выйти через sigquit
					write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
				else if	(data->exit_status == 130)
					write(STDOUT_FILENO, "\n", 1);
			}
			else
				data->exit_status = 1;
		}
		pid = waitpid(-1, &status, 0);
	}
	if (g_pid == -100)
		data->exit_status = 130;
	g_pid = -1;
}
