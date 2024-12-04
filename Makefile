# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:34:37 by abergman          #+#    #+#              #
#    Updated: 2024/12/04 16:56:47 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

OBJDIR 			= bin
SRC				:= $(shell find . -type f -name "*.c")

OBJS			:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

HEADERS 		= ./header/minishell.h

DEBUG			= -fsanitize=address,leak,undefined

CC				= cc -o3 -Wall -Wextra -Werror -g3

RM				= @rm -f

$(OBJDIR)/%.o: ./%.c $(HEADERS)
		@mkdir -p $(dir $@)
		$(CC) -c $< -o $@

$(NAME): $(OBJDIR) $(HEADERS) $(OBJS)
		$(shell hostname > /goinfre/hostname)
		$(CC) $(OBJS) -o $(NAME) -lreadline
		@echo "\n$(GREEN)$(BOLD)[ ★ SUCCESS ★ ]$(BOLD_R)$(RESET): The program is ready. You can use './minishell' for execute.\n"

all: $(NAME)

$(LIBFT):
		@make -C ./libft

$(OBJDIR):
	@mkdir $@

clean:
	$(RM) -rf $(OBJDIR)
	@make -C ./libft clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	$(RM) /goinfre/hostname
	@make -C ./libft fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re

BOLD	= \e[1m
BOLD_R	= \e[0m

GREEN	= \033[0;32m
RESET	= \033[0m
