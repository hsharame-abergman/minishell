/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:09:24 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/07 20:00:57 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define TOKEN_WORD 1
# define OPTION 2
# define PIPE 3
# define REDIRECT_INPUT 4
# define REDIRECT_OUTPUT 5
# define FIND_DELIMITER 6
# define APPEND_MODE 7
# define ENVIRONMENT 8
# define CHAR_QUOTE 9
# define CHAR_DQUOTE 10

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

bool	ft_isspace(char c);
bool	ft_isoperator(char c);
t_token	*new_token(char *value, int type);
void	add_token(t_token **token_list, char value, int type);
int	get_type(char *token);
void	init_tokens(t_token **token_list, char *input, int *i);
int	lexer(char *input);

#endif
