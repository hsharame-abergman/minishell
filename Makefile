# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abergman <abergman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:34:37 by abergman          #+#    #+#              #
#    Updated: 2024/09/28 13:35:33 by abergman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

OBJDIR 			= ./bin
SRC				= $(shell find . -name "*.c")
OBJS			:= $(SRC:./%.c=$(OBJDIR)/%.o)

HEADERS 		= ./includes.h

CC				= cc -g3 -Wall -Wextra -Werror -O3 -pthread

RM				= rm -f

$(OBJDIR)/%.o: ./%.c
		$(CC) -c $< -o $@

$(NAME): $(OBJDIR) $(HEADERS) $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

$(OBJDIR):
	@mkdir $@
	@echo "Creating object directory..."

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.SILENT:
.PHONY: all clean fclean re
