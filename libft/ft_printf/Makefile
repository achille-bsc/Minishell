# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 01:01:24 by alegrix           #+#    #+#              #
#    Updated: 2025/03/08 23:07:22 by alegrix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

OBJ = ft_printf/ft_printf.o\
	  ft_printf/ft_puthexai.o\
	  ft_printf/ft_putchari.o\
	  dprintf/ft_dprintf.o\
	  dprintf/dputhexai.o\
	  dprintf/dputchari.o\

${NAME} : ${OBJ}
	ar crs ${NAME} ${OBJ}

all: ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f $(NAME)

re: fclean all
