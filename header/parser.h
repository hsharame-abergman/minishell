/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:51:28 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/15 22:18:23 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_parser_type
{
	CMD		= 1,
	ARGUMENT,
	Q_ARGUMENT,
	DQ_ARGUMENTS,
	FLAG,
	NODE_PIPE,
	REDIRECT_OUT,
	REDIRECT_IN,
	NODE_HEREDOC,
	NODE_APPEND,
	ERROR	= -1
}	t_parser_type;

typedef struct s_ast
{
	char			*value;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

bool	is_redirection_token(int type);
bool	is_word_token(int type);
int		get_pars_type(char *value, int type);
bool	is_flag(char *s);
bool	is_cmd(char *value);
t_ast	*create_node(char *value, int type);
int		ft_strcmp(char *s1, char *s2);
t_ast	*parser_cmd(t_token *token, t_ast *last);
t_ast	*parser_pipe(t_token *token, t_ast *last);
t_ast	*parser_redirect(t_token **token, t_ast *last);
t_ast	*init_tree(t_token **token_list);
t_ast	*parser(t_token **token_list);
void	affiche_ast(t_ast *node);

#endif