NAME = polymorphism
SRC 	= main.cpp\
			Animal.cpp\
			Cat.cpp\
			Dog.cpp\
			WrongAnimal.cpp\
			WrongCat.cpp

OBJ		= $(SRC:.cpp=.o)
FLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= c++
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all