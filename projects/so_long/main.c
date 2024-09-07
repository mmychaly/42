/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:25:46 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/07 05:39:36 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*int key_handler(int keycode, t_data *data)
{
	if (keycode == 9)
	{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	}

}
int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}*/


int	main(int argc, char **argv)
{
	t_data data;
	int i;
	
	if (argc != 2 )
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	init_map(argv, &data);
	check_map(&data);
	init_map(argv, &data);
/*	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	data.win_ptr = mlx_new_window(data.mlx_ptr, 1280, 640, "So long!");
	if (!data.win_ptr)
	{
		perror("ERROR");
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		exit(EXIT_FAILURE);
	}

	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_hook(data.win_ptr, 2, 0, key_handler, &data);

	mlx_loop(data.mlx_ptr);*/
	i = 0;
	while (i < (data.map_height))
	{
		printf("afte wh data->map[%i] == %s \n", i, data.map[i]);
		i++;
	}
	printf("coin_counter %i\n", data.coin_counter);
	printf("exit_counter %i\n", data.exit_counter);
	printf("departure_counter %i\n", data.departure_counter);
	printf("map_height %i\n", data.map_height);
	printf("map_width %i\n", data.map_width);
	printf("player y == %i x == %i\n", data.player.y, data.player.x);
	free_strs(&data);
	return (0);
}