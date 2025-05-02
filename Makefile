CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

LIBFT = libft
LIBFTPRINTF = libft/ft_printf

SRCS = src/main.c src/redirection.c src/set_env.c src/varenv.c src/freeall.c src/execute.c

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
