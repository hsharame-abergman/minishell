# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:34:37 by abergman          #+#    #+#              #
#    Updated: 2024/11/27 17:32:59 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

OBJDIR 			= bin
SRC				:= $(shell find . -type f -name "*.c")

OBJS			:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

HEADERS 		= ./header/minishell.h

CC				= @cc -g3 -Wall -Wextra -Werror -O3 -fsanitize=address,leak,undefined 

RM				= @rm -f

$(OBJDIR)/%.o: ./%.c $(HEADERS)
		@mkdir -p $(dir $@)
		$(CC) -c $< -o $@

$(NAME): $(OBJDIR) $(HEADERS) $(OBJS)
		$(shell hostname > /goinfre/hostname)
		$(CC) $(OBJS) -o $(NAME) -lreadline
		@clear
		@echo "$(GREEN)$(BOLD)[ ★ SUCCESS ★ ]$(BOLD_R)$(RESET): The program is ready. You can use './minishell' for execute."

all: $(NAME)

$(LIBFT):
		@make -C ./libft

$(OBJDIR):
	@clear
	@mkdir $@
	@echo "$(YELLOW)[  PREPARING  ]$(RESET): Directory '$@' is created."
	@echo "$(YELLOW)[ COMPILATION ]$(RESET): Creating files in progress..."

clean:
	$(RM) -rf $(OBJDIR)
	@make -C ./libft clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	$(RM) /goinfre/hostname
	@make -C ./libft fclean --no-print-directory

re: fclean all

# .SILENT:
.PHONY: all clean fclean re

BOLD	= \e[1m
BOLD_R	= \e[0m

YELLOW	= \033[0;33m
GREEN	= \033[0;32m
RESET	= \033[0m
