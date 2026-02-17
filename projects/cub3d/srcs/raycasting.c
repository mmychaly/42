/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:47:47 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 03:41:51 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_textured_line(t_data *data, int x)
{
	int				tex_size;
	double			step;
	unsigned int	color;
	int				y;

	tex_size = TEX_SIZE;
	data->ray.tex_x = (int)(data->ray.wall_x * tex_size);
	step = (double)tex_size / data->ray.line_height;
	data->ray.tex_pos = (data->ray.draw_start - ((WIN_H
					- data->ray.line_height) / 2.0)) * step;
	y = data->ray.draw_start;
	while (y <= data->ray.draw_end)
	{
		data->ray.tex_y = (int)data->ray.tex_pos & (tex_size - 1);
		data->ray.tex_pos += step;
		color = get_texture_color(data->ray.current_texture,
				data->ray.tex_x, data->ray.tex_y);
		put_pixel(data, x, y, color);
		y++;
	}
}

void	define_side_dist(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y)
			* data->ray.delta_dist_y;
	}
}

void	define_intersection(t_data *data)
{
	while (data->map[data->ray.map_y][data->ray.map_x] != '1')
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
	}
	if (data->ray.side == 0)
		data->ray.wall_dist = (data->ray.side_dist_x - data->ray.delta_dist_x);
	else
		data->ray.wall_dist = (data->ray.side_dist_y - data->ray.delta_dist_y);
}

void	define_current_texture(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.wall_x = data->player.pos_y + data->ray.wall_dist
			* data->ray.ray_dir_y;
	else
		data->ray.wall_x = data->player.pos_x + data->ray.wall_dist
			* data->ray.ray_dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
	if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
		data->ray.current_texture = &data->west;
	else if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		data->ray.current_texture = &data->east;
	else if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		data->ray.current_texture = &data->north;
	else if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
		data->ray.current_texture = &data->south;
}

void	raycasting(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		data->ray.camera_x = 2 * x / (double)WIN_W - 1;
		data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x
			* data->ray.camera_x;
		data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y
			* data->ray.camera_x;
		data->ray.map_x = (int)data->player.pos_x;
		data->ray.map_y = (int)data->player.pos_y;
		data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
		data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
		define_side_dist(data);
		define_intersection(data);
		define_coordinates(data);
		define_current_texture(data);
		draw_textured_line(data, x);
		x++;
	}
}
