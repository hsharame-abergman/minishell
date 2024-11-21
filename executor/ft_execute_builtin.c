/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/11/21 15:38:22 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
Executes the given command if it is a builtin command
Return 127 if the command not found and 0 or 1 if method was be runs
 */
int	ft_execute_builtin(t_store *store, t_cmd *command)
{
	int	res;

	res = EXIT_CMD_NOT_FOUND;
	if (!command->error)
	{
		if (ft_strncmp(command->value, "cd", 3) == 0)
			res = builtin_cd(store, command->args);
		else if (ft_strncmp(command->value, "echo", 5) == 0)
			res = builtin_echo(command->args);
		else if (ft_strncmp(command->value, "env", 4) == 0)
			res = builtin_env(store, command->args);
		else if (ft_strncmp(command->value, "exit", 5) == 0)
			res = builtin_exit(store, command->args);
		else if (ft_strncmp(command->value, "export", 7) == 0)
			res = builtin_export(store, command->args);
		else if (ft_strncmp(command->value, "pwd", 4) == 0)
			res = builtin_pwd(store);
		else if (ft_strncmp(command->value, "unset", 6) == 0)
			res = builtin_unset(store, command->args);
		return (res);
	}
	return (res);
}
