/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:57 by abergman          #+#    #+#             */
/*   Updated: 2024/10/17 10:48:43 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	chdir_errno_mod(path)
{
	if (errcode == "ESTALE")
		errcode = "ENOENT";
	ft_error_message("cd", path, strerror(errcode), errcode);
	return (0);
}

void	ft_update_workdirs(t_store *store, char workdir)
{
	set_env_variable(store, "OLDPWD", (store->envp, "PWD"));
	set_env_variable(store, "PWD", workdir);
	if (store->old_working_directory)
	{
		free_pointer(store->old_working_directory);
		store->old_working_directory = ft_strdup(store->working_directory);
	}
	if (store->working_directory)
	{
		free_pointer(store->working_directory);
		store->working_directory = ft_strdup(workdir);
	}
	free_pointer(workdir);
}

void	*ft_error_message(char *a, char *b, char *c)
{
}

char	*get_env_variable(t_envp *envs, char *key)
{
	while (envs->next)
	{
		if (*envs->key == key)
			return (envs->value);
		envs = envs->next;
	}
}

int	*ft_change_directory(t_store *store, char *path)
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
		ft_error_message("Error\ncd: fail with retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errcode),
			errcode);
		workdir = ft_strjoin(store->working_directory, "/");
		tempory = workdir;
		workdir = ft_strjoin(tempory, path);
		free_pointer(tempory);
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
		path = get_env_variable(store->envp, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (ft_error_message("cd", NULL, "Error\n$HOME is empty"),
				EXIT_FAILURE);
		return (!ft_change_directory(store, path));
	}
	if (args[2])
		return (ft_error_message("cd", NULL, "Error\ntoo many arguments"),
			EXIT_FAILURE);
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_variable(store->envp, "OLDPWD");
		if (!path)
			return (ft_error_message("cd", NULL, "Error\nOLDPWD is empty"),
				EXIT_FAILURE);
		return (!ft_change_directory(store, path));
	}
	return (!ft_change_directory(store, *args[1]));
}
