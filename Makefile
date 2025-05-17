CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

LIBFT = libft
LIBFTPRINTF = libft/ft_printf

SRCS =	parser.c \
		libUtils/lst.c \
		src/execute.c src/freeall.c src/main.c \
		src/redirection.c src/set_env.c \
		src/varenv.c \
		src/built-in/echo.c src/built-in/env.c src/built-in/export.c src/built-in/unset.c \
		src/parsing/parser.c src/parsing/parsing.c src/parsing/tokener.c \
		src/parsing/utils.c


OBJS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT) -lreadline -lftprintf -lft -L $(LIBFTPRINTF) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) -s fclean
	$(MAKE) -C $(LIBFTPRINTF) -s fclean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
