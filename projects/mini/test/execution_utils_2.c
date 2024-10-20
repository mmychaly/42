
#include "minishell.h"

void	wait_processes(t_data *data)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->prev_pipe)
		{
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			else
				ft_error_exit(1);
		}
		pid = waitpid(-1, &status, 0);
	}
}