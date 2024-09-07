#ifndef SO_LONG_H
#define SO_LONG_H

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_player
{
	int	y;
	int	x;
	void	*img;
}			t_player;

typedef struct s_check
{
	int exit;
	int	coin;
}				t_check;

typedef struct s_data
{
	char 	**map;
	int		coin_counter;
	int		exit_counter;
	int		departure_counter;
	int		map_height;
	int		map_width;
	int		tiles_height;
	int		tiles_width;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*tilesets;
	void	*departure;
	void	*departure_ctr;
	void	*exit;
	void	*exit_act;
	void	*floor;
	void	*walls;
	void	*coin;
	t_player player;
	t_check  checker; 
}	t_data;

void	free_strs(t_data *data);
void	error_exit(void);
void	write_error(int fd);
void	error_malloc_1(char *str, int fd);
void	error_malloc_2(t_data *data, char *str, int fd);
void	mixt_error(t_data *data, char symb);

char	*get_next_line(int fd);

void	init_map(char **argv, t_data *data);
void	width_counter(t_data *data);

void	check_map(t_data *data);
void	check_symb(t_data *data);
void	check_symb_utils(t_data *data, int i);
void	check_close_map(t_data *data);
void	check_close_map_utils(t_data *data, int i);

#endif