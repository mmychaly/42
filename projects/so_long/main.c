#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int	main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Hello!");
	if (!win_ptr)
	{
		perror("ERROR");
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
		exit(EXIT_FAILURE);
	}

	mlx_destroy_window(win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}