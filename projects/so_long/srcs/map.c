/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:18:14 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/11 04:48:00 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	width_counter(t_data *data)
{
	int	i;
	int	i_2;

	i = 0;
	data->map_width = 0;
	while (i < data->map_height)
	{
		i_2 = 0;
		while (data->map[i][i_2] != '\n')
		{
			if (i == 0)
				data->map_width += 1;
			i_2++;
			if (data->map[i][i_2] == '\0')
				break ;
		}
		if (i_2 != data->map_width)
			mixt_error(data, 'L');
		i++;
	}
}

void	creat_map(t_data *data, char **temp, char *str, int fd)
{
	int	i;

	i = 0;
	while (str != NULL)
	{
		data->map = temp;
		str = get_next_line(fd);
		if (str != NULL)
		{
			i = 0;
			data->map_height += 1;
			temp = malloc(sizeof(char *) * (data->map_height));
			if (temp == NULL)
				error_malloc_2(data, str, fd);
			while (i < (data->map_height - 1))
			{
				temp[i] = data->map[i];
				i++;
			}
			temp[i] = str;
			free(data->map);
		}
	}
	data->map = temp;
}

void	init_map(char **argv, t_data *data)
{
	char	**temp;
	char	*str;
	int		fd;
	int		i;

	data->map_height = 0;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit();
	str = get_next_line(fd);
	if (str == NULL)
		write_error(fd);
	data->map_height += 1;
	temp = malloc(sizeof(char *) * (data->map_height));
	if (temp == NULL)
		error_malloc_1(str, fd);
	temp[i] = str;
	creat_map(data, temp, str, fd);
	close(fd);
	width_counter(data);
}
