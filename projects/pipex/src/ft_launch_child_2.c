/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:53 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/10 00:42:54 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_out(char *argv, int pipefd)
{
	int	fd_out;

	fd_out = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
		error_open_outfile(pipefd);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd_out");
		free_pipe(pipefd);
		close(pipefd);
		close(fd_out);
		exit (EXIT_FAILURE);
	}
	close(fd_out);
	if (dup2(pipefd, STDIN_FILENO) == -1)
	{
		perror("dup2 pipefd[0]");
		free_pipe(pipefd);
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
	if (argv[3][0] == '\0')
		error_empty_cmd();
	strs_argv = ft_split(argv[3], ' ');
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
