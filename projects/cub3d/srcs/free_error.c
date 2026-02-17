/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:34:44 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 02:35:17 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	destroy_game(data);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->ea)
		free(data->ea);
	if (data->we)
		free(data->we);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->map)
	{
		free_strs(data->map);
		data->map = NULL;
	}
}

void	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	error_wo_exit(char *message)
{
	if (message)
		printf("Error\n%s\n", message);
	return (-1);
}

void	error_with_exit(t_data *data, char *msg, char *to_free, char **split)
{
	if (msg)
		printf("Error\n%s\n", msg);
	if (split)
		free_strs(split);
	if (to_free)
		free(to_free);
	if (data->fd > 0)
	{
		free_gnl(data->fd);
		close(data->fd);
	}
	free_all(data);
	exit(1);
}
