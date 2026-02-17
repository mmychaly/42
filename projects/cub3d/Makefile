NAME = cub3D
SRC_F = srcs/free_error.c\
		srcs/free_error_2.c \
		srcs/main.c \
		srcs/parser_utils.c \
		srcs/parser.c \
		srcs/parser_textures.c \
		srcs/parser_textures_utils.c \
		srcs/parser_map.c \
		srcs/parser_flood.c \
		srcs/parser_map_utils.c \
		srcs/creat_game.c \
		srcs/creat_game_utils.c \
		srcs/movement.c \
		srcs/movement_utils.c \
		srcs/raycasting.c \
		srcs/raycasting_utils.c \
		srcs/parcer_utils_2.c \
		srcs/init.c
CC = cc
FLAGS = -Wall -Werror -Wextra
LIB = -Lminilibx-linux -lmlx_Linux -Llibft -lft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
RM = rm -f

$(NAME): $(SRC_F)
	@make all -C libft
	@make all -C minilibx-linux
	$(CC) $(FLAGS) $^ -o $@ $(LIB) -Iincludes

all: $(NAME)

clean:
	make clean -C libft
	make clean -C minilibx-linux

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re