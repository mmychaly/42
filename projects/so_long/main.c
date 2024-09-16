/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:25:46 by mmychaly          #+#    #+#             */
/*   Updated: 2024/09/12 15:06:17 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_handler(int keycode, t_data *data)
{
	int flag;

	flag = 1;
	if (keycode == 65307)
	{
		write(2, "close what key_handler", 22);
		free_all(data);
		exit(0);
	}
	else if (keycode == 122 || keycode == 119)
	{
		ft_printf("code key w == %i \n", keycode);
		key_w(data);
	}
	else if (keycode == 115 || keycode == 115)
	{
		ft_printf("code key s == %i \n", keycode);
		key_s(data);
	}
	else if (keycode == 100 || keycode == 100)
	{
		ft_printf("code key d == %i \n", keycode);
		key_d(data);
	}
	else if (keycode == 113 || keycode == 97)
	{
		ft_printf("code key a == %i \n", keycode);
		key_a(data);
	}
	else
		ft_printf("code key == %i \n", keycode);
	if (flag == 1 && data->coin_counter == 0) //Сохранить адрес выхода 
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_act, data->exit_x*64, data->exit_y*64);
		flag--;
	}
	return (0);
}

int	close_window(t_data *data)
{
	ft_printf("close in  close_window");
	free_all(data);
	exit(0);
	return (1);
}


int	main(int argc, char **argv)
{
	t_data data;
	
	if (argc != 2 )
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	init_map(argv, &data);
	check_map(&data);
	init_map(argv, &data);
	printf("Apres init_map\n");
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		error_exit();
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map_width * 64, data.map_height * 64, "So long!");
	if (!data.win_ptr)
	{
		perror("ERROR");
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	loading_images(&data);
	put_walls(&data);
	put_floor(&data);
	put_sprit(&data);
	mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, key_handler, &data);
	mlx_loop(data.mlx_ptr);
//	free_strs(&data);
	return (0);
}

/*
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
	*/