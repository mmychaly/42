/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:53 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/08 06:13:20 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_out(char *argv, int pipefd)
{
	int	fd_out;

	fd_out = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
	{
		perror("open infile");
		close(pipefd);
		exit (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_out");
		close(pipefd);
		close(fd_out);
		exit (EXIT_FAILURE);
	}
	close(fd_out);
	if (dup2(pipefd, STDIN_FILENO) == -1)
	{
		perror("dup2 pipefd[0]");
		close(pipefd);
		exit (EXIT_FAILURE);
	}
	close(pipefd);
}

void	ft_launch_child_2(char **argv, char *envp[], int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	close(pipefd[1]);
	ft_redirection_out(argv[4], pipefd[0]);
	strs_argv = ft_split(argv[3], ' ');
	if (strs_argv == NULL)
		ft_error_exit(1);
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
