/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:53:36 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:48:40 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* 	Executes built-in pwd command and displays current path to working dir. */
/* 	Returns 0 if successful, 1 if error found. */
int	builtin_pwd(t_store *store)
{
	char	buffer[PATH_MAX];
	char	*cwd;

	(void)buffer;
	if (store->working_directory)
	{
		ft_putendl_fd(store->working_directory, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = 0;
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ft_error_handler("pwd", NULL, strerror(g_exit_code), g_exit_code);
	return (EXIT_FAILURE);
}
