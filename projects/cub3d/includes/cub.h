/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 03:55:58 by mmychaly          #+#    #+#             */
/*   Updated: 2025/02/25 01:28:38 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 800
# define WIN_H 600
# define TEX_SIZE 64
# define ROT_SPEED 0.005
# define MOVE_SPEED 0.005
# define MOUSE_SPEED 0.006

typedef struct s_mouse
{
	int			delta_x;
	int			last_x;
	double		old_dir_x;
	double		old_plane_x;
	double		rot;
}				t_mouse;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		direction;
}				t_player;

typedef struct s_keys_stat
{
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_r;
	int			key_l;
}				t_keys_stat;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct s_ray_cast
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	t_img_data	*current_texture;
}				t_ray_cast;

typedef struct s_data
{
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	int			f;
	int			c;
	char		**map;
	int			map_height;
	int			map_width;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			fd;
	char		*line;
	t_img_data	north;
	t_img_data	south;
	t_img_data	west;
	t_img_data	east;
	t_img_data	image;
	t_player	player;
	t_keys_stat	keys;
	t_ray_cast	ray;
	t_mouse		mouse;
}				t_data;

int				ft_atoi(const char *nptr);
void			*ft_memset(void *s, int c, size_t n);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *s);
char			*get_next_line(int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

void			free_strs(char **strs);
void			free_all(t_data *data);
void			window_error(t_data *data);
void			error_with_exit(t_data *data, char *msg, char *to_free,
					char **split);
int				error_wo_exit(char *message);

void			printf_map(t_data *data);
void			remove_newline(char *str);
int				define_colors(char *str);
int				check_first_line(char *str);
int				get_map_dimensions(t_data *data, int i, int j,
					int *counter_pos);
void			init_map(t_data *data, char *str, int fd, char **temp);
int				check_map_borders(t_data *data);
int				is_valid_map_char(char c);
int				define_colors(char *str);
char			*trim_end_spaces(char *str);
void			init_map(t_data *data, char *str, int fd, char **temp);
void			parse_textures_and_colors(t_data *data, int fd);
void			parse_map_lines(t_data *data, int fd);
int				check_map_validity(t_data *data);
void			parse_cub_file(t_data *data, char *map_path);
void			init_data(t_data *data, char *map_path);
int				check_map_closure(t_data *data);
void			pad_map(t_data *data);
int				check_map_closure_flood(t_data *data);
int				check_map_universal(t_data *data);
char			*join_tokens(char **tokens, int start_index);
int				is_all_textures_and_colors_set(t_data *data);
char			*remove_all_spaces(const char *s);
void			check_texture_file(char *path, t_data *data, char **split);

void			init_game(t_data *data);
void			init_player_direction(t_data *data);
void			creat_floor_celling(t_data *data);
int				draw_img(t_data *data);
void			creat_game(t_data *data);

void			loading_texture(t_data *data, t_img_data *texture, char *path);
void			init_player_dir_y(t_data *data);
void			init_player_dir_x(t_data *data);
void			put_pixel(t_data *data, int x, int y, int color);
unsigned int	get_texture_color(t_img_data *texture, int x, int y);

void			raycasting(t_data *data);
void			define_side_dist(t_data *data);
void			define_intersection(t_data *data);
void			define_coordinates(t_data *data);
void			define_current_texture(t_data *data);
void			draw_textured_line(t_data *data, int x);

int				key_press_handler(int keycode, t_data *data);
int				key_release_handler(int keycode, t_data *data);
void			keys_stat(t_data *data);
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);

void			move_forward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
int				handle_mouse(int x, int y, t_data *data);

void			error_exit(t_data *data, char *str);
void			destroy_game(t_data *data);
int				close_window(t_data *data);
int				is_str_numeric(char **s);
void			check_unique_textures(t_data *data);

#endif
