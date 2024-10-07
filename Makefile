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
SRC				= ./lexer/*.c
OBJS			:= $(SRC:./lexer/%.c=$(OBJDIR)/%.o)
HEADERS 		= ./header/minishell.h

CC				= cc -g3 -Wall -Wextra -Werror -O3 -pthread
INCLUDES		= -I./libft
LIBFT			= ./libft/libft.a
RM				= rm -f

$(OBJDIR)/%.o: ./%.c
		$(CC) -c $< -o $@

$(NAME): $(LIBFT) $(OBJDIR) $(HEADERS) $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LIBFT) $(INCLUDES)

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
