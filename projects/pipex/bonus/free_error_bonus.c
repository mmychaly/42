/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:31:04 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/09 21:24:35 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_empty_cmd(void)
{
	write(2, "Error: Empty command\n", 21);
	free_pipe(0);
	exit(127);
}

void	error_cmd(void)
{
	write(2, "Error: option\n", 14);
	free_pipe(0);
	exit(127);
}

void	free_error_cmd(char **strs_argv)
{
	ft_free_strs(strs_argv);
	free_pipe(0);
	exit(127);
}

void	error_open_outfile(int pipefd)
{
	perror("open outfile");
	free_pipe(pipefd);
	close(pipefd);
	exit (1);
}

void	error_dup2_out(int prev_pipe)
{
	write(2, "Error: dup2 prev_pipe\n", 22);
	free_pipe(prev_pipe);
	close(prev_pipe);
	exit (EXIT_FAILURE);
}
