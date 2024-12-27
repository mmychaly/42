NAME = philo
SRC_F = src/init.c \
		src/main.c \
		src/monitoring.c \
		src/routine.c \
		src/utils_2.c \
		src/utils.c
OBJS = $(SRC_F:.c=.o)
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

$(NAME): $(OBJS)
	$(CC) -g -pthread $(FLAGS) $^ -o $@ -Iincludes

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
