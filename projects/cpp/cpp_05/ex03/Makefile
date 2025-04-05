NAME = intern
SRC 	= srcs/main.cpp\
			srcs/Bureaucrat.cpp\
			srcs/Form.cpp\
			srcs/ShrubberyCreationForm.cpp\
			srcs/RobotomyRequestForm.cpp\
			srcs/PresidentialPardonForm.cpp\
			srcs/Intern.cpp


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