CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

LIBFT = libft
LIBFTPRINTF = libft/ft_printf

# TODO: Add this to the SRCS when files will be created
# src/built-in/cd.c src/built-in/pwd.c
SRCS =	src/main.c src/set_env.c src/varenv.c \
		libUtils/lst.c \
		src/utils/errors.c src/utils/freeall.c \
		src/parsing/parser.c src/parsing/parsing.c src/parsing/utils.c \
		src/parsing/verifs.c \
		src/parsing/tokener/tokener.c src/parsing/tokener/utils.c \
		src/exec/execute.c src/exec/pre_execute.c src/exec/redirection.c \
		src/exec/utils.c \
		src/built-in/echo.c src/built-in/env.c src/built-in/export.c \
		src/built-in/unset.c src/built-in/exit.c \

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
