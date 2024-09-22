NAME = so_long
SRC_F = srcs/creat_image.c \
		srcs/free_exit_1.c \
		srcs/free_exit_2.c \
		srcs/main.c \
		srcs/map_check_utils.c \
		srcs/map_check.c \
		srcs/map.c \
		srcs/movement_utils.c \
		srcs/movement.c 
CC = cc
FLAGS = -Wall -Werror -Wextra
LIB = -Lminilibx-linux -lmlx_Linux -Llibft -lft -Llibft/printf -lftprintf -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
RM = rm -f

$(NAME): $(SRC_F)
	@make all -C libft/printf
	@make all -C libft
	$(CC) $(FLAGS) $^ -o $@ $(LIB) -Iincludes

all: $(NAME)

clean:
	make clean -C libft/printf
	make clean -C libft

fclean: clean
	make fclean -C libft/printf
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re