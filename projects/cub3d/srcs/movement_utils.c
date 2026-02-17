/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:38:43 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 02:40:48 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_press_handler(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		free_all(data);
		exit(0);
	}
	if (keycode == 65361)
		data->keys.key_l = 1;
	else if (keycode == 65363)
		data->keys.key_r = 1;
	else if (keycode == 119)
		data->keys.key_w = 1;
	else if (keycode == 115)
		data->keys.key_s = 1;
	else if (keycode == 100)
		data->keys.key_d = 1;
	else if (keycode == 97)
	{
		data->keys.key_a = 1;
	}
	return (0);
}

int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == 65361)
		data->keys.key_l = 0;
	else if (keycode == 65363)
		data->keys.key_r = 0;
	else if (keycode == 119)
		data->keys.key_w = 0;
	else if (keycode == 115)
		data->keys.key_s = 0;
	else if (keycode == 100)
		data->keys.key_d = 0;
	else if (keycode == 97)
		data->keys.key_a = 0;
	return (0);
}

void	keys_stat(t_data *data)
{
	if (data->keys.key_l == 1)
		rotate_left(data);
	if (data->keys.key_r == 1)
		rotate_right(data);
	if (data->keys.key_w == 1)
		move_forward(data);
	if (data->keys.key_s == 1)
		move_backward(data);
	if (data->keys.key_d == 1)
		move_right(data);
	if (data->keys.key_a == 1)
		move_left(data);
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	speed = -ROT_SPEED;
	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(speed)
		- data->player.dir_y * sin(speed);
	data->player.dir_y = old_dir_x * sin(speed)
		+ data->player.dir_y * cos(speed);
	data->player.plane_x = data->player.plane_x * cos(speed)
		- data->player.plane_y * sin(speed);
	data->player.plane_y = old_plane_x * sin(speed)
		+ data->player.plane_y * cos(speed);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	speed = ROT_SPEED;
	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(speed)
		- data->player.dir_y * sin(speed);
	data->player.dir_y = old_dir_x * sin(speed)
		+ data->player.dir_y * cos(speed);
	data->player.plane_x = data->player.plane_x * cos(speed)
		- data->player.plane_y * sin(speed);
	data->player.plane_y = old_plane_x * sin(speed)
		+ data->player.plane_y * cos(speed);
}
