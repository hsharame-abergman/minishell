/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:45 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/17 10:30:24 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>;
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_envp
{
	char			*key;
	char			*value;
	t_envp			*next;
}					t_envp;

typedef struct s_store
{
	struct s_envp	*envp;
	char			*working_directory;
	char			*old_working_directory;
}					t_store;

# define ERR_MSG_HOME_IS_EMPTY "Error\n$HOME is empty";
# define ERR_MSG_TOO_MANY_ARGS "Error\ntoo many arguments";
# define ERR_MSG_OLDPDW_IS_EMTY "Error\nOLDPWD is empty";

#endif
