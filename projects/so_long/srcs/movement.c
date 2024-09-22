/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:00:29 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/11 21:11:22 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_w(t_data *data)
{
	if (data->map[data->player.y - 1][data->player.x] == 'E' &&
	data->coin_counter == 0)
	{
		data->player.y -= 1;
		step_end(data);
	}
	else if (data->map[data->player.y - 1][data->player.x] == 'C')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.y -= 1;
		step_coin(data);
	}
	else if (data->map[data->player.y - 1][data->player.x] == '0' ||
		data->map[data->player.y - 1][data->player.x] == 'P')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.y -= 1;
		step(data);
	}
}

void	key_s(t_data *data)
{
	if (data->map[data->player.y + 1][data->player.x] == 'E' &&
		data->coin_counter == 0)
	{
		data->player.y += 1;
		step_end(data);
	}
	else if (data->map[data->player.y + 1][data->player.x] == 'C')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.y += 1;
		step_coin(data);
	}
	else if (data->map[data->player.y + 1][data->player.x] == '0' ||
		data->map[data->player.y + 1][data->player.x] == 'P')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.y += 1;
		step(data);
	}
}

void	key_d(t_data *data)
{
	if (data->map[data->player.y][data->player.x + 1] == 'E' &&
		data->coin_counter == 0)
	{
		data->player.x += 1;
		step_end(data);
	}
	else if (data->map[data->player.y][data->player.x + 1] == 'C')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.x += 1;
		step_coin(data);
	}
	else if (data->map[data->player.y][data->player.x + 1] == '0' ||
		data->map[data->player.y][data->player.x + 1] == 'P')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.x += 1;
		step(data);
	}
}

void	key_a(t_data *data)
{
	if (data->map[data->player.y][data->player.x - 1] == 'E' &&
		data->coin_counter == 0)
	{
		data->player.x -= 1;
		step_end(data);
	}
	else if (data->map[data->player.y][data->player.x - 1] == 'C')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.x -= 1;
		step_coin(data);
	}
	else if (data->map[data->player.y][data->player.x - 1] == '0' ||
		data->map[data->player.y][data->player.x - 1] == 'P')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, data->player.x * 64, data->player.y * 64);
		data->player.x -= 1;
		step(data);
	}
}
