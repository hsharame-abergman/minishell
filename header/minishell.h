/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:45 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/17 14:00:48 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern int	g_exit_code;

typedef struct s_ast
{
	char			*value;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_store
{
	struct s_envp	*envp;
	char			*input;
	char			*working_directory;
	char			*old_working_directory;
	t_token			*token;
	t_ast			*pars;
}					t_store;


/* ************************************************************************** */
/*                     LEXER                                                  */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD = 1,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	HEREDOC,
	APPEND_MODE,
	CHAR_QUOTE,
	CHAR_DQUOTE
}	t_token_type;

void	check_pipe(t_token **token_list, char *input, int *i);
void	affiche_tokens(t_token *token_list);
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
bool	lexer(t_store *data);

/* ************************************************************************** */
/*                    PARSER                                                  */
/* ************************************************************************** */

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
