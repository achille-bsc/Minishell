# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 01:01:24 by alegrix           #+#    #+#              #
#    Updated: 2025/06/02 08:50:13 by abosc            ###   ########.fr        #
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
