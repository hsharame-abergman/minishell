# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:34:37 by abergman          #+#    #+#              #
#    Updated: 2024/10/07 20:09:19 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

OBJDIR 			= ./bin
SRC				:= $(shell find . -type f -name "*.c")
OBJS			:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

HEADERS 		= ./header/minishell.h

CC				= cc -g3 -Wall -Wextra -Werror -O3 -pthread

RM				= rm -f

$(OBJDIR)/%.o: ./%.c $(HEADERS)
		$(CC) -c $< -o $@

$(NAME): $(OBJDIR) $(HEADERS) $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

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

.SILENT:
.PHONY: all clean fclean re
