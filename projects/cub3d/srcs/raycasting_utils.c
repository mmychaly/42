/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 03:43:28 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 03:44:07 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	define_coordinates(t_data *data)
{
	data->ray.line_height = (int)(WIN_H / data->ray.wall_dist);
	data->ray.draw_start = WIN_H / 2 - data->ray.line_height / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = WIN_H / 2 + data->ray.line_height / 2;
	if (data->ray.draw_end >= WIN_H)
		data->ray.draw_end = WIN_H - 1;
}
