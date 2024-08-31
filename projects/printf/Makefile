NAME = libftprintf.a
SRC_F = ft_printf.c ft_put_symb.c ft_put_nbr.c ft_put_str.c ft_put_unsigned_nbr.c ft_put_hexadecimal.c ft_put_ptr.c
OBJ_F = $(SRC_F:.c=.o)
CC = cc
FLGAS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rcs

$(NAME): $(OBJ_F)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean: 
	$(RM) $(OBJ_F)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re