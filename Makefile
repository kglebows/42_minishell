# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 18:20:23 by kglebows          #+#    #+#              #
#    Updated: 2023/12/11 23:56:51 by kglebows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra 

# CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g

OBJDIR = ./bin
SRCDIR = ./src

SRCS	= main.c \
		exit/error.c exit/exit.c \
		parse/token.c parse/token_utils.c parse/lexer.c parse/parse.c\
		executor/ft_executor.c

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

LIBFTNAME = bin/libft/libft.a
LIBFTDIR = lib/libft
LIBFT_PATH = ./lib/libft
INCLUDE_PATH = ./include

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@OUTPUT=$$($(CC) $(CFLAGS) -I $(LIBFT_PATH) -I $(INCLUDE_PATH) -Isrc -c $< -o $@ 2>&1); \
	if [ $$? -eq 0 ]; then \
		echo "\033[0;32m$< OK!\033[0m"; \
	else \
		echo "$$OUTPUT" && echo "\033[0;31m$< KO!\033[0m" && exit 1; \
	fi

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -I $(INCLUDE_PATH) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

all: init-submodules makelibft $(NAME)

init-submodules:
	@if [ -z "$(shell ls -A $(LIBFT_PATH))" ]; then \
		git submodule init $(LIBFT_PATH); \
		git submodule update $(LIBFT_PATH); \
	fi

makelibft:
	@if [ ! -f "$(LIBFTNAME)" ]; then \
		OUTPUT=$$(make -C $(LIBFTDIR) --no-print-directory 2>&1); \
		if echo "$$OUTPUT" | grep -E "cc|ar" > /dev/null; then \
			echo "\033[0;32mLIBFT OK!\033[0m"; \
		fi; \
	fi

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -I $(INCLUDE_PATH) -lreadline -o $(NAME) $(OBJS) -L$(OBJDIR)/libft -lft

clean-empty-dirs:
	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

clean: 
	@for obj in $(OBJS); do \
		if [ -f "$$obj" ]; then \
			rm -f $$obj && echo "\033[0;33m$$obj deleted\033[0m"; \
		fi; \
	done
	@OUTPUT=$$(make -C $(LIBFTDIR) clean --no-print-directory 2>&1); \
	if echo "$$OUTPUT" | grep -E "deleted" > /dev/null; then \
		echo "\033[0;33mlibft *.o deleted\033[0m"; \
	fi
	@$(MAKE) clean-empty-dirs

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME) && echo "\033[0;33m$(NAME) deleted\033[0m"; \
	fi
	@OUTPUT=$$(make -C $(LIBFTDIR) fclean --no-print-directory 2>&1); \
	if echo "$$OUTPUT" | grep -E "deleted" > /dev/null; then \
		echo "\033[0;33mlibft.a deleted\033[0m"; \
	fi
	@$(MAKE) clean-empty-dirs

re: fclean all

.PHONY: all clean fclean norm re bonus