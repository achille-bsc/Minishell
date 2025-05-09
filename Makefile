CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

LIBFT = libft
LIBFTPRINTF = libft/ft_printf

SRCS =	commitmsg.txt files headers libUtils Makefile parser.c src \
		headers/minishell.h headers/structures.h \
		libUtils/lst.c \
		src/built-in src/execute.c src/freeall.c src/freeall.o src/main.c src/main.o \
		src/parsing src/redirection.c src/redirection.o src/set_env.c src/set_env.o \
		src/varenv.c src/varenv.o \
		src/built-in/echo.c src/built-in/env.c src/built-in/export.c src/built-in/unset.c \
		src/parsing/parser.c src/parsing/parsing.c src/parsing/tokener.c \
		src/parsing/utils.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT) -lftprintf -lft -L $(LIBFTPRINTF) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) -s fclean
	$(MAKE) -C $(LIBFTPRINTF) -s fclean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
