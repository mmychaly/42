/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:08:02 by mmychaly          #+#    #+#             */
/*   Updated: 2024/10/14 04:08:03 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_fault_execve(char **strs, char *cmd, int flag)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
	free(cmd);
	cmd = NULL;
	if (flag == 1)
		free_pipe(0);
	perror("ERROR execve");
	exit(126);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	ft_error_exit(int nb)
{
	perror("ERROR");
	if (nb == 0)
		exit(0);
	else
		exit(EXIT_FAILURE);
}

void	free_pipe(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	error_split(int flag)
{
	perror("ERROR split: ");
	if (flag == 1)
		free_pipe(0);
	exit(EXIT_FAILURE);
}