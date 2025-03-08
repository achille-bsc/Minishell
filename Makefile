CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell

LIBFT = libft
LIBFTPRINTF = libft/ft_printf

SRCS = src/main.c src/redirection.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT) -lftprintf -L $(LIBFTPRINTF) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) -s fclean
	$(MAKE) -C $(LIBFTPRINTF) -s fclean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
