# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azakharo <azakharo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 17:39:46 by azakharo          #+#    #+#              #
#    Updated: 2024/06/26 20:21:31 by azakharo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCES =	ft_printf.c \
            print_functions.c

OBJECTS = ${SOURCES:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

LIB = ar rcs

INCLUDES = -I. -I./libft

.c.o:
	${CC} ${FLAGS} ${INCLUDES} -c $< -o ${<:.c=.o} 

all: ${NAME}

${NAME}: ${OBJECTS}
	make -C libft
	cp libft/libft.a .
	mv libft.a ${NAME}
	${LIB} ${NAME} ${OBJECTS}

clean:
	${RM} ${OBJECTS}
	make clean -C libft

fclean: clean
	${RM} ${NAME}
	${RM} libft/libft.a

re: fclean all