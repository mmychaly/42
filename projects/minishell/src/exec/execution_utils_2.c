/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 04:19:01 by mmychaly          #+#    #+#             */
/*   Updated: 2024/12/04 01:44:07 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint_newline(int sig)
{
	g_sig = sig;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	close(0);
}

void	check_status(t_data *data, int status)
{
	int	signal;

	if (WIFEXITED(status))
		data->exit_status = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		data->exit_status = 128 + signal;
		if (data->exit_status == 131)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else if (data->exit_status == 130)
			write(STDOUT_FILENO, "\n", 2);
	}
	else
		data->exit_status = 1;
}

void	wait_processes(t_data *data)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (g_sig == 3)
		{
			g_sig = 0;
			kill(pid, SIGQUIT);
		}
		if (g_sig == 2)
		{
			g_sig = 0;
			kill(pid, SIGINT);
		}
		if (pid == data->last)
			check_status(data, status);
		pid = waitpid(-1, &status, 0);
	}
	handle_signals();
}
