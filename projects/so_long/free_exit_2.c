/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 05:22:58 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/12 15:08:09 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mixt_error(t_data *data, char symb)
{
	write(2, "Error\n", 6);
	if (symb == 'L')
		write(2, ": width of map is incorrect\n", 28);
	else if (symb == 'C')
		write(2, ": quantity of item is incorrect\n", 32);
	else if (symb == 'E')
		write(2, ": quantity of exit is incorrect\n", 32);
	else if (symb == 'D')
		write(2, ": quantity of starting position is incorrect\n", 45);
	else if (symb == 'S')
		write(2, ": prohibited symbols on the map\n", 32);
	else if (symb == 'F')
		write(2, ": non-rectangular shape of the map\n", 35);
	else if (symb == 'O')
		write(2, ": the map is not enclosed in walls\n", 35);
	else if (symb == 'e')
		write(2, ": exit on map not available\n", 28);
	else if (symb == 'c')
		write(2, ": coin on map not available\n", 28);
	free_strs(data);
	exit(EXIT_FAILURE);
}

void	free_all(t_data *data)
{
	if (data->coin != NULL)
		mlx_destroy_image(data->mlx_ptr, data->coin);
	if (data->player.img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->player.img);
	if (data->walls != NULL)
		mlx_destroy_image(data->mlx_ptr, data->walls);
	if (data->floor != NULL)
		mlx_destroy_image(data->mlx_ptr, data->floor);
	if (data->exit != NULL)
		mlx_destroy_image(data->mlx_ptr, data->exit);
	if (data->exit_act != NULL)
		mlx_destroy_image(data->mlx_ptr, data->exit_act);
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr != NULL)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_strs(data);
}
