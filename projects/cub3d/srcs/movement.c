/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:09:12 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 02:37:58 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
		data->player.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
		data->player.pos_y = new_y;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
		data->player.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
		data->player.pos_y = new_y;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
		data->player.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
		data->player.pos_y = new_y;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
		data->player.pos_x = new_x;
	if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
		data->player.pos_y = new_y;
}

int	handle_mouse(int x, int y, t_data *data)
{
	(void)y;
	if (data->mouse.last_x == -1)
	{
		data->mouse.last_x = x;
		return (0);
	}
	data->mouse.delta_x = x - data->mouse.last_x;
	data->mouse.last_x = x;
	if (data->mouse.delta_x == 0)
		return (0);
	data->mouse.old_dir_x = data->player.dir_x;
	data->mouse.old_plane_x = data->player.plane_x;
	data->mouse.rot = data->mouse.delta_x * MOUSE_SPEED;
	data->player.dir_x = data->player.dir_x * cos(data->mouse.rot)
		- data->player.dir_y * sin(data->mouse.rot);
	data->player.dir_y = data->mouse.old_dir_x * sin(data->mouse.rot)
		+ data->player.dir_y * cos(data->mouse.rot);
	data->player.plane_x = data->player.plane_x * cos(data->mouse.rot)
		- data->player.plane_y * sin(data->mouse.rot);
	data->player.plane_y = data->mouse.old_plane_x * sin(data->mouse.rot)
		+ data->player.plane_y * cos(data->mouse.rot);
	return (0);
}
