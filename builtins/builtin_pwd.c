/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:53:36 by abergman          #+#    #+#             */
/*   Updated: 2024/10/21 19:18:19 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Выполняет встроенную команду pwd и отображает текущий путь к рабочей директории.
	Возвращает 0, если успешно, 1, если ошибка обнаружена.
*/
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
