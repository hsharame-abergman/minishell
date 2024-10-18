/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:53:36 by abergman          #+#    #+#             */
/*   Updated: 2024/10/18 17:58:05 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	// cwd = get_cwd(buffer, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	// ft_error_message("pwd", NULL, strerror(g_exit_code), g_exit_code);
	return (EXIT_FAILURE);
}
