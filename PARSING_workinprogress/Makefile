# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 18:20:23 by kglebows          #+#    #+#              #
#    Updated: 2023/12/10 19:33:21 by kglebows         ###   ########.fr        #
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

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@OUTPUT=$$($(CC) $(CFLAGS) -Isrc -c $< -o $@ 2>&1); \
	if [ $$? -eq 0 ]; then \
		echo "\033[0;32m$< OK!\033[0m"; \
	else \
		echo "$$OUTPUT" && echo "\033[0;31m$< KO!\033[0m" && exit 1; \
	fi

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS)

clean-empty-dirs:
	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

clean: 
	@for obj in $(OBJS); do \
		if [ -f "$$obj" ]; then \
			rm -f $$obj && echo "\033[0;33m$$obj deleted\033[0m"; \
		fi; \
	done
	@$(MAKE) clean-empty-dirs

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME) && echo "\033[0;33m$(NAME) deleted\033[0m"; \
	fi
	@$(MAKE) clean-empty-dirs

re: fclean all

.PHONY: all clean fclean norm re bonus