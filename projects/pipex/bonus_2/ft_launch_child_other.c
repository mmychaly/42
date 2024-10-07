/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_other.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 02:03:48 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/05 05:37:28 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirection_between(int pipefd, int prev_pipe)
{
	if (dup2(prev_pipe, STDIN_FILENO) == -1)
	{
		perror("dup2 prev_pipe");
		close(prev_pipe);
		close(pipefd);
		exit (EXIT_FAILURE);
	}
	close(prev_pipe);
	if (dup2(pipefd, STDOUT_FILENO) == -1)
	{
		perror("dup2 pipefd[1]");
		close(pipefd);
		exit (EXIT_FAILURE);
	}
	close(pipefd);
}

void	ft_launch_other(char *argv, char *envp[], int pipefd[2], int prev_pipe)
{
	char	**strs_argv;
	char	*cmd;

	close(pipefd[0]);
	printf("in ft_launch_other\n"); //supprimer
	ft_redirection_between(pipefd[1], prev_pipe);
	if (argv[0] == '\0')
	{
		write(2, "Error: Empty command\n", 22);
		exit(1);
	}
	strs_argv = ft_split(argv, ' ');
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
