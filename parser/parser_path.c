/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:13:01 by hsharame          #+#    #+#             */
/*   Updated: 2024/12/02 13:13:34 by hsharame         ###   ########.fr       */
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
