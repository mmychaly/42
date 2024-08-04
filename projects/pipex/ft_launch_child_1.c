/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_child_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:32:34 by mmychaly          #+#    #+#             */
/*   Updated: 2024/08/03 04:18:24 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirection_in(char *argv, int pipefd)
{
		int		fd_in;
	
	fd_in = open(argv, O_RDONLY);
	if (fd_in == -1)
	{ 
		perror("open in");
		exit (EXIT_FAILURE);
	} 
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 fd_in");
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

	strs_argv = ft_split(argv[2], ' ');
	if (strs_argv == NULL)
	{
		perror("Error in split for strs_argv_1");
		exit(EXIT_FAILURE);
	}
	cmd = ft_envp_cherch(strs_argv[0], envp);
	if (cmd == NULL)
	{
		ft_free_strs(strs_argv);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	ft_redirection_in(argv[1], pipefd[1]);
	if (execve(cmd, strs_argv, NULL) == -1)
	{
		perror("execve_1");
		exit (EXIT_FAILURE);
	}
}
