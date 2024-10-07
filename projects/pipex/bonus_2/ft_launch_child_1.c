/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:34 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/05 05:36:26 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirection_in(char *argv, int pipefd)
{
	int		fd_in;

	fd_in = open(argv, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		perror("open infile");
		close(pipefd);
		exit (EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 fd_in");
		close(pipefd);
		close(fd_in);
		exit (EXIT_FAILURE);
	}
	close(fd_in);
	if (dup2(pipefd, STDOUT_FILENO) == -1)
	{
		perror("dup2 pipefd[1]");
		close(pipefd);
		exit (EXIT_FAILURE);
	}
	close(pipefd);
}

void	ft_launch_child_1(int i, char **argv, char *envp[], int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	printf("in ft_launch_child_1\n");
	close(pipefd[0]);
	ft_redirection_in(argv[i - 1], pipefd[1]);
	if (argv[i][0] == '\0')
	{
		write(2, "Error: Empty command\n", 22);
		exit(1);
	}
	strs_argv = ft_split(argv[i], ' ');
	if (strs_argv == NULL)
		ft_error_exit(1);
	strs_argv = check_strs(strs_argv);
	if (strs_argv == NULL)
	{
		write(2, "Error: command not found\n", 25);
		exit(1);
	}
	if (access(strs_argv[0], F_OK | X_OK) == 0)
	{
		cmd = ft_strdup(strs_argv[0]);
		if (cmd == NULL)
			free_fault_cmd(strs_argv);
	}
	else
		cmd = ft_envp_cherch(strs_argv[0], envp);
	if (cmd == NULL)
	{
		ft_free_strs(strs_argv);
		exit(127);
	}
	if (execve(cmd, strs_argv, envp) == -1)
		free_fault_execve(strs_argv, cmd);
}
