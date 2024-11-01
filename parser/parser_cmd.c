/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/01 15:35:11 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	PATH is an environment variable, which contains something like this:
	/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin
	
	So, each path is separated by the ":" sign. To find the path that leads to
	the appropriate command, we split each path, then try to put the command
	name, if the access(path, X_OK) function returns 0, it means that an
	executable of this name exists in this folder. So, we store the path string
	in the t_cmd node.

	example:							builtin example:
	char *value = cat 					char *value = echo
	char *path = /usr/bin/cat 			char *path = echo  
*/

char	*find_path(char **env, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		path = ft_strjoin(env[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*define_path(char *cmd)
{
	char	**env_dir;
	char	*path;
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	env_dir = ft_split(path_env, ':');
	cmd = ft_strjoin("/", cmd);
	path = find_path(env_dir, cmd);
	free(cmd);
	free_tab(env_dir);
	return (path);
}

/*
	Fill the char *path in the t_cmd node. If the command is a builtin or if it 
	is already passed with absolute path (if it contains /), we duplicate in
	this field the content of value. Otherwise, we search for the path.
*/

t_cmd	*parser_cmd(t_token *token, t_cmd *last)
{
	t_cmd	*current;

	current = create_node(token->value);
	if (last)
	{
		last->right = current;
		current->left = last;
	}
	if (is_builtin(current->value))
		current->path = ft_strdup(current->value);
	else
	{
		if (ft_strchr(current->value, '/') == NULL)
			current->path = define_path(current->value);
		else
			current->path = ft_strdup(current->value);
		check_if_exists(current);
	}
	return (current);
}

t_cmd	*handle_cmd(t_token **save, t_cmd **last, int *first)
{
	t_cmd	*current;

	current = parser_cmd(*save, *last);
	*first = 0;
	*save = (*save)->next;
	return (current);
}

void	handle_pipe(t_token **save, t_cmd **current, int *first)
{
	if (*first == 1)
	{
		error_syntax("syntax error near unexpected token `|'\n", 2);
		(*current)->error = true;
		return ;
	}
	(*current)->pipe = true;
	*save = (*save)->next;
	*first = 1;
}
