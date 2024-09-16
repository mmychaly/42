/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 01:53:19 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/12 14:59:26 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	step(t_data *data)
{
	data->step_count += 1;
	ft_printf("Number of steps == %i\n", data->step_count);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player.img, data->player.x * 64, data->player.y * 64);
}

void	step_coin(t_data *data)
{
	data->step_count += 1;
	ft_printf("Number of steps == %i\n", data->step_count);
	data->map[data->player.y][data->player.x] = '0';
	data->coin_counter -= 1;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player.img, data->player.x * 64, data->player.y * 64);
}

void	step_end(t_data *data)
{
	data->step_count += 1;
	ft_printf("Number of steps == %i\n", data->step_count);
	ft_printf("End of the game\n");
	free_all(data);
	exit (0);
}
