CC = cc
CFLAGS = -Wall -Werror -Wextra -lreadline#-fsanitize=address -g
SOURCE = main.c
OBJ = $(SOURCE:.c=.o)
NAME = Minishell
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
