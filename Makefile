# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:34:37 by abergman          #+#    #+#              #
#    Updated: 2024/11/15 19:31:09 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

OBJDIR 			= bin
SRC				:= $(shell find . -type f -name "*.c")

OBJS			:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

HEADERS 		= ./header/minishell.h

CC				= @cc -g3 -Wall -Wextra -Werror -O3 -pthread

RM				= @rm -f

$(OBJDIR)/%.o: ./%.c $(HEADERS)
		@mkdir -p $(dir $@)
		$(CC) -c $< -o $@

$(NAME): $(OBJDIR) $(HEADERS) $(OBJS)
		$(CC) $(OBJS) -o $(NAME) -lreadline
		@clear
		@echo "[ ★ SUCCESS ★ ]: The program is ready. You can use file './minishell' for execute"

all: $(NAME)

$(LIBFT):
		@make -C ./libft

$(OBJDIR):
	@clear
	@mkdir $@
	@echo "[  PREPARING  ]: Directory '$@' is created"
	@echo "[ COMPILATION ]: Creating files in progress..."

clean:
	$(RM) -rf $(OBJDIR)
	@make -C ./libft clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	@make -C ./libft fclean --no-print-directory

re: fclean all

# .SILENT:
.PHONY: all clean fclean re
