/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:53 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/06 01:55:24 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_out(char *argv, int pipefd, char **strs_argv, char *cmd)
{
	int	fd_out;

	fd_out = open(argv, O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open outfile");
		free(cmd);
		ft_free_strs(strs_argv);
		exit (EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_out");
		ft_free_all(strs_argv, cmd, fd_out);
		exit (EXIT_FAILURE);
	}
	close(fd_out);
	if (dup2(pipefd, STDIN_FILENO) == -1)
	{
		perror("dup2 pipefd[0]");
		ft_free_all(strs_argv, cmd, pipefd);
		exit (0);
	}
	close(pipefd);
}

void	ft_launch_child_2(char **argv, char *envp[], int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	strs_argv = ft_split(argv[3], ' ');
	if (strs_argv == NULL)
	{
		perror("Error in split for strs_argv_2");
		exit(EXIT_FAILURE);
	}
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = strs_argv[0];
	else
		cmd = ft_envp_cherch(strs_argv[0], envp);
	if (cmd == NULL)
	{
		ft_free_strs(strs_argv);
		exit(127);
	}
	close(pipefd[1]);
	ft_redirection_out(argv[4], pipefd[0], strs_argv, cmd);

	if (execve(cmd, strs_argv, envp) == -1)
	{
		perror("execve_2");
		free(cmd);
		ft_free_strs(strs_argv);
		exit (EXIT_FAILURE);
	}
}