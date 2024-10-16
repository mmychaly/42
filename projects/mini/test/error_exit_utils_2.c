/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:07:52 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/15 18:11:32 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_empty_cmd( int flag)
{
	write(2, "Error: Empty command\n", 21);
	if (flag == 1)
		free_pipe(0);
	exit(127);
}

void	error_cmd(int flag)
{
	write(2, "Error: option\n", 14);
	if (flag == 1)
		free_pipe(0);
	exit(127);
}

void	free_error_cmd(char **strs_argv, int flag)
{
	ft_free_strs(strs_argv);
	if (flag == 1)
		free_pipe(0);
	exit(127);
}

void	error_open_outfile(int flag)
{
	perror("open outfile");
	if (flag == 1)
		free_pipe(0);
	exit (1);
}

void	error_dup2_out(int prev_pipe, int flag)
{
	write(2, "Error: dup2 prev_pipe\n", 22);
	if (flag == 1)
	{
		free_pipe(0);
		close(prev_pipe);
	}
	exit (EXIT_FAILURE);
}
