/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:45:33 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/04 05:25:02 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_strs(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->map_height))
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void	error_exit(void)
{
	perror("Error\n");
	exit(EXIT_FAILURE);
}

void	write_error(int fd)
{
	write(2, "Error\n", 6);
	write(2, ": Empty file\n", 13);
	close(fd);
	exit(EXIT_FAILURE);
}

void	error_malloc_1(char *str, int fd)
{
	perror("Error\n");
	close(fd);
	free(str);
	exit(EXIT_FAILURE);
}

void	error_malloc_2(t_data *data, char *str, int fd)
{
	perror("Error\n");
	close(fd);
	free(str);
	data->map_height -= 1;
	free_strs(data);
	exit(EXIT_FAILURE);
}
