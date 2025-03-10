NAME = phonebook
SRC 	= srcs/main.cpp\
			srcs/Contact.cpp\
			srcs/PhoneBook.cpp

OBJ		= $(SRC:.cpp=.o)
FLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= c++
RM		= rm -f

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@ -Iincludes

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ -Iincludes

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re