/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:34 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/06 17:13:38 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_in(char *argv, int pipefd, char **strs_argv, char *cmd)
{
	int		fd_in;

	fd_in = open(argv, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		perror("open infile");
		free(cmd);
		ft_free_strs(strs_argv);
		exit (EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 fd_in");
		ft_free_all(strs_argv, cmd, fd_in);
		exit (0);
	}
	close(fd_in);
	if (dup2(pipefd, STDOUT_FILENO) == -1)
	{
		perror("dup2 pipefd[1]");
		ft_free_all(strs_argv, cmd, pipefd);
		exit (0);
	}
	close(pipefd);
}

void	ft_launch_child_1(char **argv, char *envp[], int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	strs_argv = ft_split(argv[2], ' ');
	if (strs_argv == NULL)
		ft_error_exit(1);
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = strs_argv[0];
	else
		cmd = ft_envp_cherch(strs_argv[0], envp);
	if (cmd == NULL)
	{
		ft_free_strs(strs_argv);
		exit(127);
	}
	close(pipefd[0]);
	ft_redirection_in(argv[1], pipefd[1], strs_argv, cmd);
	if (execve(cmd, strs_argv, envp) == -1)
	{
		perror("execve_1");
		free(cmd);
		ft_free_strs(strs_argv);
		exit (0);
	}
}
