NAME = pipex
SRC_F = src/*.c
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

$(NAME): $(SRC_F)
	@make all -C libft
	$(CC) $(FLAGS) $^ -o $@ -Llibft -lft -Iincludes

all: $(NAME)

clean: 
	make clean -C libft

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re