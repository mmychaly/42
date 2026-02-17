NAME = libft.a
SRC_F = ft_atoi.c ft_calloc.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_memmove.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c free_error.c get_next_line.c
OBJ_F = $(SRC_F:.c=.o)
BONUS_SRC = ft_lstadd_front.c ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstclear.c ft_lstnew.c ft_lstmap.c ft_lstsize.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)
CC = cc
FLAG = -Wall -Wextra -Werror
AR = ar -rcs 
RM = rm -f

$(NAME): $(OBJ_F)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ_F) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(BONUS_OBJ)
	$(AR) $(NAME) $^

.PHONY: all clean fclean re bonus