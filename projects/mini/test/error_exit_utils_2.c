/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:07:52 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/22 04:10:26 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_empty_cmd(t_data *data)
{
	write(2, "Error: Empty command\n", 21);
	if (data->flag_pipe > 0)
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

void	free_error_cmd(char **strs_argv, t_data *data)
{
	ft_free_strs(strs_argv);
	if (data->flag_pipe > 0)
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

