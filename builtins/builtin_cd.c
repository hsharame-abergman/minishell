/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:57 by abergman          #+#    #+#             */
/*   Updated: 2024/12/06 18:09:50 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	chdir_errno_mod(char *path)
{
	if (g_exit_code == ESTALE)
		g_exit_code = ENOENT;
	return (ft_error_handler("cd", path, strerror(ENOENT), 1));
}

static void	ft_update_workdirs(t_store *store, char *workdir)
{
	ft_set_env(store, "OLDPWD", ft_get_env_value(store->envp, "PWD"));
	ft_set_env(store, "PWD", workdir);
	if (store->old_working_directory)
	{
		ft_free_pointer(store->old_working_directory);
		store->old_working_directory = ft_strdup(store->working_directory);
	}
	if (store->working_directory)
	{
		ft_free_pointer(store->working_directory);
		store->working_directory = ft_strdup(workdir);
	}
	ft_free_pointer(workdir);
}

static int	ft_change_directory(t_store *store, char *path)
{
	char	*workdir;
	char	*tempory;
	char	cwd[PATH_MAX];

	workdir = NULL;
	if (path && ft_strcmp(path, "~") == 0)
		path = ft_get_env_value(store->envp, "HOME");
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	workdir = getcwd(cwd, PATH_MAX);
	if (!workdir)
	{
		ft_error_handler(B_CD, EMSG_FR, strerror(g_exit_code), g_exit_code);
		ft_error_handler("getcwd", EMSG_AC, strerror(g_exit_code), g_exit_code);
		workdir = ft_strjoin(store->working_directory, "/");
		tempory = workdir;
		workdir = ft_strjoin(tempory, path);
		ft_free_pointer(tempory);
	}
	else
		workdir = ft_strdup(cwd);
	ft_update_workdirs(store, workdir);
	return (0);
}

int	builtin_cd(t_store *store, char **args)
{
	char	*path;

	if (!args || !args[1])
	{
		path = ft_get_env_value(store->envp, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (ft_error_handler(B_CD, NULL, "Error\n$HOME is empty",
					EXIT_FAILURE));
		return (ft_change_directory(store, path));
	}
	if (ft_isspace(args[1][0]))
		return (ft_error_handler(B_CD, args[1], strerror(STDERR_FILENO), 1));
	if (args[2])
		return (ft_error_handler(B_CD, NULL, "Error\ntoo many arguments",
				EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_get_env_value(store->envp, "OLDPWD");
		if (!path)
			return (ft_error_handler(B_CD, NULL, "Error\nOLDPWD is empty",
					EXIT_FAILURE));
		return (ft_change_directory(store, path));
	}
	return (ft_change_directory(store, args[1]));
}
