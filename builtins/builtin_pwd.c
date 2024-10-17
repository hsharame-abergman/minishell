/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:53:36 by abergman          #+#    #+#             */
/*   Updated: 2024/10/17 12:45:22 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	buildin_pwd(t_store *store)
{
	char	buffer[PATH_MAX];
	char	cwd;

	if (store->working_directory)
	{
		ft_putendl_fd(store->working_directory, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = get_cwd(buffer, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ft_error_message("pwd", NULL, strerror(errcode), errcode);
	return (EXIT_FAILURE);
}
