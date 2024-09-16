#ifndef SO_LONG_H
#define SO_LONG_H

#include "libft/libft.h"
#include "libft/printf/ft_printf.h"
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
	int		exit_y;
	int		exit_x;
	int		departure_counter;
	int		map_height;
	int		map_width;
	int		step_count;
	int		tiles_height;
	int		tiles_width;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*tilesets;
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
void	free_all(t_data *data);

char	*get_next_line(int fd);
int		ft_printf(const char *str, ...);

void	init_map(char **argv, t_data *data);
void	width_counter(t_data *data);

void	check_map(t_data *data);
void	check_symb(t_data *data);
void	check_symb_utils(t_data *data, int i);
void	check_close_map(t_data *data);
void	check_close_map_utils(t_data *data, int i);


void	put_walls(t_data *data);
void	put_floor(t_data *data);
void	put_sprit(t_data *data);
void	loading_images(t_data *data);

int	close_window(t_data *data);
int key_handler(int keycode, t_data *data);
void	key_w(t_data *data);
void	key_s(t_data *data);
void	key_d(t_data *data);
void	key_a(t_data *data);
void	step(t_data *data);
void	step_coin(t_data *data);
void	step_end(t_data *data);

#endif