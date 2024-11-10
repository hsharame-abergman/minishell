# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:34:37 by abergman          #+#    #+#              #
#    Updated: 2024/11/10 16:14:36 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

OBJDIR 			= ./bin
SRC				:= $(shell find . -type f -name "*.c")
C_FLAGS	:= -I /Users/$(USER)/.brew/Cellar/readline/8.1.*/include/ -lreadline -L /Users/$(USER)/.brew/Cellar/readline/8.1.*/lib/

OBJS			:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

HEADERS 		= ./header/minishell.h

CC				= cc -g3 -Wall -Wextra -Werror -O3 -pthread -v 

RM				= rm -f

$(OBJDIR)/%.o: ./%.c $(HEADERS)
		@mkdir -p $(dir $@)
		$(CC) -c $< -o $@

$(NAME): $(OBJDIR) $(HEADERS) $(OBJS)
		$(CC) $(OBJS) -o $(NAME) -lreadline

all: $(NAME)

$(LIBFT):
		make -C ./libft

$(OBJDIR):
	@mkdir $@
	@echo "Creating object directory..."

clean:
	$(RM) -rf $(OBJDIR)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.SILENT: .
.PHONY: all clean fclean re
