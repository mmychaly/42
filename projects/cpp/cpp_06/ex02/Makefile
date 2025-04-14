NAME = dynamic
SRC 	= srcs/main.cpp\
			srcs/Base.cpp

OBJ		= $(SRC:.cpp=.o)
FLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= c++
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@  -Iincludes

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all