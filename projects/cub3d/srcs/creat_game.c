/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 03:42:15 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 03:43:15 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_game(t_data *data)
{
	data->mouse.last_x = -1;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		error_exit(data, "Error\n:Failed mlx_init\n");
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "CUB3D!");
	if (!data->win)
		error_with_exit(data, NULL, NULL, NULL);
	data->image.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->image.img)
		error_exit(data, "Error\n:Failed to load image\n");
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_length, &data->image.endian);
	if (!data->image.addr)
		error_exit(data, "Error\n:Failed to get image data\n");
	loading_texture(data, &data->north, data->no);
	loading_texture(data, &data->south, data->so);
	loading_texture(data, &data->east, data->ea);
	loading_texture(data, &data->west, data->we);
	if (!data->north.img || !data->south.img || !data->west.img
		|| !data->east.img)
		error_exit(data, "Error\n:image is not loaded\n");
}

void	init_player_direction(t_data *data)
{
	if (data->player.direction == 'N' || data->player.direction == 'S')
		init_player_dir_y(data);
	else if (data->player.direction == 'E' || data->player.direction == 'W')
		init_player_dir_x(data);
}

void	creat_floor_celling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				put_pixel(data, x, y, data->c);
			else
				put_pixel(data, x, y, data->f);
			x++;
		}
		y++;
	}
}

int	draw_img(t_data *data)
{
	keys_stat(data);
	creat_floor_celling(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

void	creat_game(t_data *data)
{
	init_game(data);
	init_player_direction(data);
	draw_img(data);
	mlx_hook(data->win, 17, 1L << 17, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_handler, data);
	mlx_hook(data->win, 6, 1L << 6, handle_mouse, data);
	mlx_loop_hook(data->mlx, draw_img, data);
	mlx_loop(data->mlx);
}
