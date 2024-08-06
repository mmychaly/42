/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:27:49 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/06 02:13:02 by mmychaly         ###   ########.fr       */
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
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_1 = fork();
	if (pid_1 == -1)
	{
		perror("pid_1");
		exit(EXIT_FAILURE);
	}
	if (pid_1 == 0)
		ft_launch_child_1(argv, envp, pipefd);
	pid_2 = fork();
	if (pid_2 == -1)
	{
		perror("pid_2");
		exit(EXIT_FAILURE);
	}
	if (pid_2 == 0)
		ft_launch_child_2(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);

	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char *envp[])
{

	if (argc == 5)
	{
		if (access(argv[1], F_OK) == -1)
		{
			if (access(argv[4], F_OK) == -1)
				ft_create_empty_file(argv[4]);
			int	fd;
			fd = open(argv[4], O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
			perror("open in ft_create_empty_file");
			exit (EXIT_FAILURE);
			}
			write(fd, "0\n", 2);
			close(fd);
			perror("Error");
			exit(0);
		}
		if ((access(argv[4], F_OK) == -1))
			ft_create_empty_file(argv[4]);
		ft_execution(argv, envp);
	}
	else
	{
		write(2, "Error: Incorrect number of arguments\n", 37);
		exit (EXIT_FAILURE);
	}
	return (0);
}
