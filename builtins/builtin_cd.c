/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:57 by abergman          #+#    #+#             */
/*   Updated: 2024/11/04 17:15:01 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	chdir_errno_mod(char *path)
{
	int	g_exit_code;

	g_exit_code = 0;
	(void)path;
	if (g_exit_code == ESTALE)
		g_exit_code = ENOENT;
	ft_error_handler("cd", path, strerror(g_exit_code), g_exit_code);
	return (0);
}

void	ft_update_workdirs(t_store *store, char *workdir)
{
	ft_set_env(store, "OLDPWD", ft_get_env(store->envp, "PWD"));
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

int	ft_change_directory(t_store *store, char *path)
{
	char	*workdir;
	char	*tempory;
	char	cwd[PATH_MAX];

	workdir = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	workdir = getcwd(cwd, PATH_MAX);
	if (!workdir)
	{
		ft_error_handler("Error\ncd: fail with retrieving current directory",
			"getcwd: cannot access parent directories", strerror(g_exit_code),
			g_exit_code);
		workdir = ft_strjoin(store->working_directory, "/");
		tempory = workdir;
		workdir = ft_strjoin(tempory, path);
		ft_free_pointer(tempory);
	}
	else
	{
		workdir = ft_strdup(cwd);
	}
	ft_update_workdirs(store, workdir);
	return (1);
}

int	builtin_cd(t_store *store, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]))
	{
		path = ft_get_env(store->envp, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (ft_error_handler("cd", NULL, "Error\n$HOME is empty",
					EXIT_FAILURE));
		return (!ft_change_directory(store, path));
	}
	if (args[2])
		return (ft_error_handler("cd", NULL, "Error\ntoo many arguments",
				EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_get_env(store->envp, "OLDPWD");
		if (!path)
			return (ft_error_handler("cd", NULL, "Error\nOLDPWD is empty",
					EXIT_FAILURE));
		return (!ft_change_directory(store, path));
	}
	return (!ft_change_directory(store, args[1]));
}
