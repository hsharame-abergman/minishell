/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:45 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/10 16:29:48 by abergman         ###   ########.fr       */
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

# define _GNU_SOURCE

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include "errno.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define CMD_NOT_FOUND 127

extern int	g_exit_code;

typedef struct s_redirect
{
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	*delimiter;
	int		stdin_backup;
	int		stdout_backup;
	int		heredoc_quotes;
}	t_redirect;

typedef struct s_cmd
{
	char			*value;
	char			*path;
	char			**args;
	bool			pipe;
	int				*fd_pipe;
	bool			error;
	t_redirect		*redirect;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum s_mode {
	SINDLE_COMMAND,
	INTERACTIVE
}	t_mode;

typedef struct s_store
{
	char			**envp;
	char			*input;
	char			*working_directory;
	char			*old_working_directory;
	int				error;
	t_mode			mode_usage;
	t_token			*token;
	t_cmd			*pars;
	pid_t			pid;
}					t_store;

/* ************************************************************************** */
/*                     Utils                                                  */
/* ************************************************************************** */

void	free_tab(char **tab);
int		error_syntax(char *s, int error);
int		initial_store(t_store *store, char **envp);
char	*ft_strjoin2(char *dest, char *str);
int		ft_error_handler(char *cmd, char *detail, char *errmsg, int errcode);
int		ft_default_error(int res);
int		check_input_arguments(t_store *store, int ac, char **av, char **envp);
void	ft_free_pointer(void *pointer);
int		ft_search_flag(char *str, char flag);
int		ft_set_env(t_store *store, char *key, char *value);
int		ft_env_is_valid(char *node);
int		ft_count_env(char **envp);
int		ft_remove_env(t_store *store, int index);
int		ft_get_env_index(char **envp, char *key);

/* clear */
void	ft_free_store(t_store *store, int history);
/* env */
char	*ft_get_env(char **envp, char *search);
/* executor */
int		ft_executor(t_store *store);
int		ft_restore_io(t_redirect *redirect);
void	ft_close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void	ft_close_fds(t_cmd *cmds, bool close_backups);
void	ft_exit_program(t_store *store, int exit_code);
int		ft_check_io(t_redirect *redirect);
int		ft_set_pipe_fds(t_cmd *cmds, t_cmd *cmd);
int		ft_execute_command(t_store *store, t_cmd *cmd);
int		ft_redirect_io(t_redirect *redirect);

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
	END,
	ERROR
}	t_token_type;

void	reset_tokens(t_token **token);
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
/*                     Expander                                               */
/* ************************************************************************** */

void	expander(t_store *data, t_token **token_list);
bool	check_escape(char *str, int i);
char	*get_env_value(char *input, int *i);
char	*check_if_var(char *input);
bool	expander_heredoc(char *input);

/* ************************************************************************** */
/*                    Parser                                                  */
/* ************************************************************************** */

void	open_file_trunc(t_redirect *trunc, char *filename);
void	open_file_append(t_redirect *trunc, char *filename);
void	open_input(t_redirect *trunc, char *filename);
void	parse_append(t_cmd **cmd, t_token **token);
void	parse_input(t_cmd **cmd, t_token **token);
void	parse_trunc(t_cmd **cmd, t_token **token);
char	*temp_file(int number);
bool	heredoc_succes(t_store *data, t_redirect *heredoc);
void	parse_heredoc(t_store *data, t_cmd **cmd, t_token **token);
bool	is_builtin(char *s);
char	*find_path(char **env, char *cmd);
char	*define_path(char *cmd);
void	add_redirect(t_token **save, t_cmd **current, t_store *data);
t_cmd	*handle_cmd(t_token **save, t_cmd **last, int *first);
void	handle_pipe(t_token **save, t_cmd **current, int *first);
bool	is_redirection_token(int type);
bool	is_word_token(int type);
t_cmd	*create_node(char *value);
int		count_args(t_token *save);
void	add_args(t_token **save, t_cmd *cmd);
t_cmd	*parser_cmd(t_token *token, t_cmd *last);
t_cmd	*init_tree(t_token **token_list, t_store *data);
void	parser(t_store *data, t_token *token_list);
void	affiche_ast(t_cmd *node);
void	create_redirect(t_cmd *cmd);
void	check_if_exists(t_cmd *node);
void	cmd_error(t_cmd *node, int i);
char	*tab_to_str(char **token);
char	*fill_str(char *res, char **token);

/* ************************************************************************** */
/*                    Builtins                                                */
/* ************************************************************************** */

int		ft_builtins(t_store *store, t_cmd *command);
int		is_builtins(t_store *store, char **args);
int		builtin_cd(t_store *store, char **args);
int		builtin_pwd(t_store *store);
int		builtin_echo(char **av);
int		builtin_env(t_store *store, char **av);
int		builtin_exit(t_store *store, char **av);
int		builtin_export(t_store *store, char **av);
int		builtin_unset(t_store *store, char **av);

/* ************************************************************************** */
/*                    Signals                                                 */
/* ************************************************************************** */

void	signals_ignore(void);
void	signal_ctrl_c(int sign);
void	signals_interactive(void);

#endif
