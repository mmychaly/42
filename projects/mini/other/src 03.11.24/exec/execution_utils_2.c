/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 04:19:01 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/28 20:46:54 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t child_running = 0;

// Обработчик для SIGINT в родительском процессе
void handle_sigint_parent(int sig)
{
	(void) sig;
    if (!child_running) {
		write(STDOUT_FILENO, "\nminishell$ ", 12);
//        fflush(stdout);
    }
}

// Обработчик для SIGINT в дочернем процессе
void handle_sigint_child(int sig) 
{
    (void)sig;
    exit(130); // Завершаем дочерний процесс
}

/*void handle_sigint_parent(int sig) //не нужны
{
	(void)sig;

   	write(STDOUT_FILENO, "\nminishell$ ", 12);
}*/


void	wait_processes(t_data *data)
{
	int	pid;
	int	status;
	int signal;

	child_running = 1;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		child_running = 0;
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
}
