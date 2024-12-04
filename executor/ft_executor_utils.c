/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:22:41 by abergman          #+#    #+#             */
/*   Updated: 2024/12/04 15:26:43 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_close_executer(int exit_code, t_store *store)
{
	ft_close_fds(store->pars, 1);
	ft_exit_program(store, exit_code);
}

int	ft_command_is_dir(char *value)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(value, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}
