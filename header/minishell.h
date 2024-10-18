/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:45 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/18 18:27:08 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *      _____                                                                   
 *  ___|    _|__  ____  ____   _  ____  ______  __   _  ______  ____    ____    
 * |    \  /  | ||    ||    \ | ||    ||   ___||  |_| ||   ___||    |  |    |   
 * |     \/   | ||    ||     \| ||    | `-.`-. |   _  ||   ___||    |_ |    |_  
 * |__/\__/|__|_||____||__/\____||____||______||__| |_||______||______||______| 
 *     |_____|                                                                  
 *                                                                                 
 */

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
# include "errno.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern int	g_exit_code;

typedef	struct s_redirect
{
	
}	t_redirect;

typedef struct s_cmd
{
	char			*value;
	char			*path;
	char			**args;
	bool			pipe;
	t_redirect		*redirect;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

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

typedef enum s_mode {
	SINDLE_COMMAND,
	INTERACTIVE
} t_mode;

typedef struct s_store
{
	struct s_envp	*envp;
	char			*input;
	char			*working_directory;
	char			*old_working_directory;
	t_mode			mode_usage;
	t_token			*token;
	t_cmd			*pars;
}					t_store;

int		initial_store(t_store *store, char **envp);
int	ft_error_message(char *error_msg, char *description, int quotes, int res);
int		ft_standart_error(int res);
int	check_input_arguments(t_store *store, int ac, char **av, char **envp);

/* ************************************************************************** */
/*                     Lexer                                                  */
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
	CHAR_DQUOTE,
	END
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
/*                    Parser                                                  */
/* ************************************************************************** */

t_cmd	*handle_command(t_token **save, t_cmd **last_node, int *first);
void	handle_pipe(t_token **save, t_cmd **current, int *first);
bool	is_redirection_token(int type);
bool	is_word_token(int type);
t_cmd	*create_node(char *value);
int		count_args(t_token *save);
void	add_args(t_token *save, t_cmd *cmd);
t_cmd	*parser_cmd(t_token *token, t_cmd *last);
t_cmd	*init_tree(t_token **token_list);
void	parser(t_store *data, t_token *token_list);
void	affiche_ast(t_cmd *node);

/* ************************************************************************** */
/*                    Builtins                                                */
/* ************************************************************************** */

int	is_builtins(t_store *store, char **av);
int	ft_builtins(t_store *store, char **av);
int	builtin_cd(t_store *store, char **args);
int	builtin_pwd(t_store *store);
void	builtin_echo(char **av);
void builtin_env(void);
void builtin_exit(void);
void	builtin_export(void);

#endif
