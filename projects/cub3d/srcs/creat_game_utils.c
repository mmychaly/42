/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_game_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:50:55 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 03:44:45 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_texture_color(t_img_data *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

void	loading_texture(t_data *data, t_img_data *texture, char *path)
{
	int	height;
	int	width;

	height = TEX_SIZE;
	width = TEX_SIZE;
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (!texture->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		free_all(data);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		printf("Error\nFailed to get texture data: %s\n", path);
		free_all(data);
		exit(1);
	}
}

void	init_player_dir_y(t_data *data)
{
	if (data->player.direction == 'N')
	{
		data->player.dir_x = 0.0;
		data->player.dir_y = -1.0;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0.0;
	}
	else if (data->player.direction == 'S')
	{
		data->player.dir_x = 0.0;
		data->player.dir_y = 1.0;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0.0;
	}
}

void	init_player_dir_x(t_data *data)
{
	if (data->player.direction == 'E')
	{
		data->player.dir_x = 1.0;
		data->player.dir_y = 0.0;
		data->player.plane_x = 0.0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.direction == 'W')
	{
		data->player.dir_x = -1.0;
		data->player.dir_y = 0.0;
		data->player.plane_x = 0.0;
		data->player.plane_y = -0.66;
	}
}
