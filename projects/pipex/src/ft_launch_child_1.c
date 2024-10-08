/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:34 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/10 00:42:45 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_launch_child_1(char **argv, char *envp[], int pipefd[2])
{
	char	**strs_argv;
	char	*cmd;

	close(pipefd[0]);
	ft_redirection_in(argv[1], pipefd[1]);
	if (argv[2][0] == '\0')
		error_empty_cmd();
	strs_argv = ft_split(argv[2], ' ');
	if (strs_argv == NULL)
		error_split();
	if (access(strs_argv[0], F_OK | X_OK) == 0)
		cmd = ft_strdup(strs_argv[0]);
	else
		cmd = ft_envp_cherch(strs_argv[0], envp);
	if (cmd == NULL)
		free_error_cmd(strs_argv);
	if (execve(cmd, strs_argv, envp) == -1)
		free_fault_execve(strs_argv, cmd);
}
