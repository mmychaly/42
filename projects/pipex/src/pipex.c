/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:27:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/10 00:42:23 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execution(char **argv, char *envp[])
{
	int	pid_1;
	int	pid_2;
	int	pipefd[2];
	int	status;

	if (pipe(pipefd) == -1)
		ft_error_exit(1);
	pid_1 = fork();
	if (pid_1 == -1)
		ft_error_exit(1);
	if (pid_1 == 0)
		ft_launch_child_1(argv, envp, pipefd);
	pid_2 = fork();
	if (pid_2 == -1)
		ft_error_exit(1);
	if (pid_2 == 0)
		ft_launch_child_2(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		ft_error_exit(1);
}

int	main(int argc, char **argv, char *envp[])
{
	if (envp == NULL || envp[0][0] == '\0')
	{
		write(2, "Error: empty envp\n", 18);
		exit(EXIT_FAILURE);
	}
	if (argc == 5)
		ft_execution(argv, envp);
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 37);
		exit (EXIT_FAILURE);
	}
	return (0);
}
