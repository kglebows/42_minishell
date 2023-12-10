CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g
SOURCE = testing.c executor_utils.c executor.c heredoc.c pathfinder.c redirector.c duping.c builtin.c\
	../builtins/ft_echo.c ../builtins/ft_env.c ../builtins/ft_exit.c ../builtins/ft_export.c\
	../builtins/ft_pwd.c ../builtins/ft_unset.c
OBJ = $(SOURCE:.c=.o)
NAME = executor_test
LIBFT		= ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(SOURCE) $(CFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@cd libft && make && make clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
