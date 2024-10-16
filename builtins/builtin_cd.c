/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:57 by abergman          #+#    #+#             */
/*   Updated: 2024/10/16 15:52:52 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*error_message()
{
	
}

char	*get_argv(t_envp *envs, char *key)
{
	while (envs->next)
	{
		if (*envs->key == key)
			return (envs->value);
		envs = envs->next;
	}
}

int	*ft_change_directory(t_minishell *store, char *path)
{
	return (0);
}

int	builtin_cd(t_minishell *store, char **args)
{
	char	*path;
	char	*ERR_MSG_HOME_IS_EMPTY;
	char	*ERR_MSG_TOO_MANY_ARGS;
	char	*ERR_MSG_OLDPDW_IS_EMTY;

	ERR_MSG_HOME_IS_EMPTY = "Error\n$HOME is empty";
	ERR_MSG_TOO_MANY_ARGS = "Error\ntoo many arguments";
	ERR_MSG_OLDPDW_IS_EMTY = "Error\nOLDPWD is empty";
	if (!args || !args[1] || ft_isspace(args[1][0])) // TODO: add strcmp for --
	{
		path = get_argv(store->envp, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (ft_error_message("cd", NULL, ERR_MSG_HOME_IS_EMPTY),
				EXIT_FAILURE);
		return (!ft_change_directory(store, path));
	}
	if (args[2])
		return (ft_error_message("cd", NULL, ERR_MSG_TOO_MANY_ARGS), EXIT_FAILURE);
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_argv(store->envp, "OLDPWD");
		if (!path)
			return (ft_error_message("cd", NULL, ERR_MSG_OLDPDW_IS_EMTY),
				EXIT_FAILURE);
		return (!ft_change_directory(store, path));
	}
	return (!ft_change_directory(store, *args[1]));
}
