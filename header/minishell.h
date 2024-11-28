/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:45 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/28 16:49:50 by abergman         ###   ########.fr       */
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

# include "../libft/libft.h"
# include "errno.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_exit_code;

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define EXIT_GENERAL_ERROR 2
# define EXIT_CMD_NOT_EXECUT 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_INTERRUPTED 130
# define EXIT_ERROR_FORMAT 258

typedef struct s_redirect
{
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	char			*delimiter;
	int				stdin_backup;
	int				stdout_backup;
	int				heredoc_quotes;
}					t_redirect;

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
}					t_cmd;

typedef struct s_token
{
	char			*value;
	int				type;
	bool			is_adjacent;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef enum e_mode
{
	SINDLE_COMMAND,
	INTERACTIVE
}					t_mode;

typedef enum e_free_arg
{
	FREE_DEST,
	FREE_SRC
}		t_free_arg;

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

int					check_input(char *str);
bool				void_input(t_store *data);
bool				check_bracket(char *str);
bool				check_several_operator(char *str);
int					error_syntax(char *s, int error, bool code);
int					ft_init_store(t_store *store, char **envp);
int					ft_error_handler(char *cmd, char *detail, char *errmsg,
						int errcode);
int					ft_defauit_error(int res);
int					ft_check_args(t_store *store, int ac, char **av,
						char **envp);
void				ft_free_pointer(void *pointer);
int					ft_search_flag(char *str, char flag);
int					ft_env_is_valid(char *node);
int					ft_count_env(char **envp);
int					ft_remove_env(t_store *store, int index);
char				**ft_get_paths_from_envp(t_store *store);
char				*ft_find_valid_command_path(char *command, char **paths);
void				ascii_welcome(void);
char				*ft_hostname(void);
char				*ft_create_label_for_readline(t_store *store);

/* clear */
void				free_tab(char **tab);
void				ft_free_store(t_store *store, int history);
void				free_token(t_token **token_list);
void				free_redirect(t_redirect *node);
void				free_cmd(t_cmd **cmd);
char				*ft_strjoin_free(char *dest, char *str, t_free_arg i);

/* env */
char				*ft_get_env_value(char **envp, char *search);
int					ft_get_env_index(char **envp, char *key);
int					ft_set_env(t_store *store, char *key, char *value);

/* executor */
int					ft_executor(t_store *store);
int					ft_restore_io(t_redirect *redirect);
void				ft_close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void				ft_close_fds(t_cmd *cmds, bool close_backups);
void				ft_exit_program(t_store *store, int exit_code);
int					ft_check_io(t_redirect *redirect);
int					ft_set_pipe_fds(t_cmd *cmds, t_cmd *cmd);
int					ft_execute_builtin(t_store *store, t_cmd *command);
int					ft_execute_command(t_store *store, t_cmd *cmd);
int					ft_redirect_io(t_redirect *redirect);
int					ft_command_is_dir(char *value);
int					ft_check_command_not_found(t_store *data, t_cmd *cmd);
char				*ft_parser_path(t_store *store, char *value);
/* pipes */
int					ft_create_pipes(t_store *store);

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
}					t_token_type;

bool				init_lexer(t_store *data);
char				*check_pipe(t_token **token_list, char *input, int *i);
char				*input_pipe(t_token **token_list, char *input, int *i);
void				reset_tokens(t_token **token);
void				affiche_tokens(t_token *token_list);
int					token_quotes(t_token **token_list, char *input, int *i,
						char quote);
void				token_quotes_error(t_token **token_list, char *input,
						char quote);
bool				quotes(t_token **token_list, char *input, int *i);
void				token_word(t_token **token_list, char *input, int *i);
bool				ft_isspace(char c);
bool				ft_isoperator(char c);
t_token				*new_token(char *value, int type);
void				add_token(t_token **token_list, char *value, int type);
int					get_type(char *token);
bool				init_tokens(t_token **token_list, char *input, int *i);
bool				lexer(t_store *data);

/* ************************************************************************** */
/*                     Expander                                               */
/* ************************************************************************** */

char				*escape_digit(char *str);
char				*replace_var_error(char *res, int *i);
char				*process_var(t_store *data, char *res, int *i);
char				*process_var_error(char *res, int *i);
char				*process_digit_escape(char *res, int *i);
void				variables_expansion(t_store *data, t_token *token, int *i);
void				expander(t_store *data, t_token **token_list);
bool				check_escape(char *str, int i);
char				*replace_var(t_store *data, char *res, int *i);
char				*get_env_value(t_store *data, char *input, int *i);
char				*check_if_var(t_store *data, char *input);
bool				expander_heredoc(t_store *data, char *input);

/* ************************************************************************** */
/*                    Parser                                                  */
/* ************************************************************************** */

void				cmd_error(t_cmd *node, int i);
bool				reset_redirect(t_redirect *redir, bool infile);
bool				open_file_trunc(t_redirect *trunc, char *filename);
bool				open_file_append(t_redirect *append, char *filename);
bool				open_input(t_redirect *input, char *filename);
bool				parse_append(t_cmd **cmd, t_token **token);
bool				parse_input(t_cmd **cmd, t_token **token);
bool				parse_trunc(t_cmd **cmd, t_token **token);
char				*temp_file(int number);
bool				heredoc_succes(t_store *data, t_redirect *heredoc);
bool				parse_heredoc(t_store *data, t_cmd **cmd, t_token **token);
bool				is_builtin(char *s);
char				*find_path(char **env, char *cmd);
char				*define_path(char *cmd);
void				add_redirect(t_token **save, t_cmd **current,
						t_store *data);
t_cmd				*handle_cmd(t_token **save, t_cmd **last, int *first);
void				handle_pipe(t_token **save, t_cmd **current, int *first);
bool				is_redirection_token(int type);
bool				is_word_token(int type);
t_cmd				*create_node(char *value);
int					count_args(t_token *save);
void				add_args(t_token **save, t_cmd *cmd);
t_cmd				*parser_cmd(t_token *token, t_cmd *last);
t_cmd				*init_tree(t_token **token_list, t_store *data);
bool				parser(t_store *data, t_token *token_list);
void				affiche_ast(t_cmd *node);
void				create_redirect(t_cmd *cmd);
void				check_if_exists(t_cmd *node);
char				*tab_to_str(char **token);
char				*fill_str(char *res, char **token);
char				*join_args(char *stash, char *str, char *str2);
void				fill_args(t_token **save, t_cmd *cmd, int count);

/* ************************************************************************** */
/*                    Builtins                                                */
/* ************************************************************************** */

struct				s_format
{
	int				counter;
};

# define B_CD "cd"
# define B_PWD "pwd"
# define B_ECHO "echo"
# define B_ENV "env"
# define B_EXIT "exit"
# define B_EXPORT "export"
# define B_UNSET "unset"
# define B_LS "ls"

# define EMSG_FR "fail with retrieving current directory"
# define EMSG_AC "cannot access parent directories"

int					builtin_cd(t_store *store, char **args);
int					builtin_pwd(t_store *store);
int					builtin_echo(char **av);
int					builtin_env(t_store *store, char **av);
int					builtin_exit(t_store *store, char **av);
int					builtin_export(t_store *store, char **av);
int					builtin_unset(t_store *store, char **av);
int					builtin_ls(t_store *store);

/* ************************************************************************** */
/*                    Signals                                                 */
/* ************************************************************************** */

void				signals_ignore(void);
void				signal_ctrl_c(int sign);
void				ft_set_signals_interactive(void);

#endif
