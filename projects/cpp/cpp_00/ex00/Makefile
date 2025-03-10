NAME	= megaphone
SRC 	= megaphone.cpp
OBJ		= $(SRC:.cpp=.o)
FLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= c++
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean