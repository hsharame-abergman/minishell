/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:09:24 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/11 16:06:47 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD = 1,
	OPTION,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	APPEND_MODE,
	ENVIRONMENT,
	CHAR_QUOTE,
	CHAR_DQUOTE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

int		token_quotes(t_token **token_list, char *input, int *i, char quote);
void	token_quotes_error(t_token **token_list, char *input, char quote);
void	quotes(t_token **token_list, char *input, int *i);
void	token_word(t_token **token_list, char *input, int *i);
bool	ft_isspace(char c);
bool	ft_isoperator(char c);
t_token	*new_token(char *value, int type);
void	add_token(t_token **token_list, char *value, int type);
int		get_type(char *token);
void	init_tokens(t_token **token_list, char *input, int *i);
int		lexer(char *input);

#endif
