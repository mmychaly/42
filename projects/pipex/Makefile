NAME = pipex
BONUS = pipex_bonus
SRC_F = src/free_strs_fd.c \
		src/free_strs_fd_2.c \
		src/ft_envp_cherch.c \
		src/ft_launch_child_1.c \
		src/ft_launch_child_2.c \
		src/pipex.c
BONUS_SRC_F = bonus/free_error_bonus.c \
				bonus/free_strs_fd_bonus.c \
				bonus/ft_envp_cherch_bonus.c \
				bonus/ft_launch_child_1_bonus.c \
				bonus/ft_launch_child_2_bonus.c \
				bonus/ft_launch_child_other_bonus.c \
				bonus/launch_here_doc_bonus.c \
				bonus/pipex_utils_bonus.c \
				bonus/pipex_bonus.c
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

$(NAME): $(SRC_F)
	@make all -C libft
	$(CC) $(FLAGS) $^ -o $@ -Llibft -lft -Iincludes

$(BONUS): $(BONUS_SRC_F)
	@make all -C libft
	$(CC) $(FLAGS) $^ -o $@ -Llibft -lft -Ibonus

all: $(NAME)

bonus: $(BONUS)

clean: 
	make clean -C libft

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
	$(RM) $(BONUS);

re: fclean all

.PHONY: all clean fclean re