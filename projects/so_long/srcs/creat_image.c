/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:35:04 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/16 14:32:24 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->walls, x * 64, y * 64);
			x++;
		}
		y++;
	}
}

void	put_floor(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '0' || data->map[y][x] == 'C'
					|| data->map[y][x] == 'E' || data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->floor, x * 64, y * 64);
			x++;
		}
		y++;
	}
}

void	put_sprit(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (y == data->player.y && x == data->player.x)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->player.img, data->player.x * 64, data->player.y * 64);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr,
					data->win_ptr, data->coin, x * 64, y * 64);
			else if (data->map[y][x] == 'E' && data->coin_counter != 0)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->exit, x * 64, y * 64);
			else if (data->map[y][x] == 'E' && data->coin_counter == 0)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->exit_act, x * 64, y * 64);
			x++;
		}
		y++;
	}
}

void	loading_images(t_data *data)
{
	int	height;
	int	width;

	data->floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/grey_pressed.xpm", &height, &width);
	data->walls = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/space.xpm", &height, &width);
	data->player.img = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/pers_tail.xpm", &height, &width);
	data->coin = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/coin_tail.xpm", &height, &width);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/portal_off.xpm", &height, &width);
	data->exit_act = mlx_xpm_file_to_image(data->mlx_ptr,
			"img/portal_on.xpm", &height, &width);
	if (!data->floor || !data->walls || !data->player.img
		|| !data->coin || !data->exit || !data->exit_act)
	{
		write(2, "Error\n: image is not loaded\n", 28);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	put_walls(data);
	put_floor(data);
	put_sprit(data);
}
