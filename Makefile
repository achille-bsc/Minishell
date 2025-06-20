CC = cc
CFLAGS = -Wall -Wextra -Werror -g -o3
NAME = minishell

LIBFT = libft
LIBFTPRINTF = libft/ft_printf

OBJS_DIR = obj

SRCS =	src/main.c src/set_env.c src/varenv.c \
		libUtils/lst.c libUtils/lst2.c \
		src/utils/errors.c src/utils/freeall.c src/utils/freeall2.c \
		src/parsing/parsing.c src/parsing/utils.c src/parsing/verifs.c \
		src/parsing/tokener/tokener.c src/parsing/tokener/utils.c \
		src/parsing/tokener/tokener2.c \
		src/exec/execute.c src/exec/pre_execute.c src/exec/here_doc.c \
		src/exec/redirection.c src/exec/utils.c \
		src/built-in/echo.c src/built-in/env.c src/built-in/export.c \
		src/built-in/unset.c src/built-in/exit.c src/built-in/cd.c \
		src/utils/arrays.c \
		src/parsing/varenv/replacer.c \
		src/built-in/pwd.c \
		src/signals/signals.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT) -lreadline -lftprintf -lft -L $(LIBFTPRINTF) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) -s fclean
	$(MAKE) -C $(LIBFTPRINTF) -s fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
