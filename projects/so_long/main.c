/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:25:46 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/16 13:34:52 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_handler(int keycode, t_data *data)
{
	int	flag;

	flag = 1;
	if (keycode == 65307)
	{
		free_all(data);
		exit(0);
	}
	else if (keycode == 119)
		key_w(data);
	else if (keycode == 115)
		key_s(data);
	else if (keycode == 100)
		key_d(data);
	else if (keycode == 97)
		key_a(data);
	if (flag == 1 && data->coin_counter == 0)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_act,
			data->exit_x * 64, data->exit_y * 64);
		flag--;
	}
	return (0);
}

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	init_map(argv, &data);
	check_map(&data);
	init_map(argv, &data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		free_strs(&data);
		error_exit();
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			data.map_width * 64, data.map_height * 64, "So long!");
	if (!data.win_ptr)
		window_error(&data);
	loading_images(&data);
	mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_handler, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
