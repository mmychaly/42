/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strs_fd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:23:08 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/10 00:43:02 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_empty_cmd(void)
{
	write(2, "Error: Empty command\n", 21);
	free_pipe(0);
	exit(127);
}

void	error_split(void)
{
	perror("ERROR split: ");
	free_pipe(0);
	exit(EXIT_FAILURE);
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
