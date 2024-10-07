/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:53 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/05 05:37:49 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirection_out(char *argv, int pipefd, int flag)
{
	int	fd_out;

	if (flag == 1)
		fd_out = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
	{
		perror("open outfile");
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

void	ft_launch_child_2(int i, char **argv, char *envp[], int prev_pipe)
{
	char	**strs_argv;
	char	*cmd;
	int		flag;

	flag = 0;
	printf("in ft_launch_child_2\n"); //Supprimer
	if ((ft_strncmp(argv[1], "here_doc", strlen(argv[1]))) == 0)
		flag = 1;
	ft_redirection_out(argv[i + 1], prev_pipe , flag);
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
