/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/11/05 11:48:24 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_builtins(t_store *store, t_cmd *command)
{
	int res;

	res =  127; // 127 is the exit code for command not found
	if (is_builtins(store, &command->value))
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
	return (0);
}
