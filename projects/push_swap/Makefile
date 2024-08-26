NAME = push_swap
BONUS = checker
SRC_F = srcs/*.c
BONUS_SRC_F = checker_bonus/*.c
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

$(NAME): $(SRC_F)
	@make all -C libft
	$(CC) $(FLAGS) $^ -o $@ -Llibft -lft -Iincludes

$(BONUS): $(BONUS_SRC_F)
	@make all -C libft
	$(CC) $(FLAGS) $^ -o $@ -Llibft -lft -Ichecker_bonus

all: $(NAME)

bonus: $(BONUS)

clean: 
	make clean -C libft

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
	$(RM) $(BONUS);

re: fclean all

.PHONY: all clean fclean re bonus