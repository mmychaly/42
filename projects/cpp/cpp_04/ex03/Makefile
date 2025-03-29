NAME = interface
SRC 	= srcs/main.cpp\
			srcs/AMateria.cpp\
			srcs/Character.cpp\
			srcs/MateriaSource.cpp\
			srcs/Ice.cpp\
			srcs/Cure.cpp

OBJ		= $(SRC:.cpp=.o)
FLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= c++
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@ -Iincludes

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all