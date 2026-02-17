/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:34:19 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/15 02:34:31 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	error_exit(t_data *data, char *str)
{
	printf("%s", str);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	destroy_game(t_data *data)
{
	if (data->north.img)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx, data->west.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}
