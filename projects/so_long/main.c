#include "minilibx-linux/mlx.h"
#include <stdlib.h>

typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
}				t_data;

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_FAILURE);
}


int	main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Hello!");
	if (!data.win_ptr)
	{
		perror("ERROR");
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		exit(EXIT_FAILURE);
	}

	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_hook(data.win_ptr, 2, 0, key_press, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}