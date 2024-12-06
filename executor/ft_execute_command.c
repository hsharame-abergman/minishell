/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:44:42 by abergman          #+#    #+#             */
/*   Updated: 2024/12/06 18:18:22 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
 *	Executes the command's system binary file if it can be found
 *	among the environment executable paths.
 *	Returns EXIT_CMD_NOT_FOUND if a path to the executable bin file cannot be
 *	found. Returns 1 in case of failure to run existing, executable file.
 */
static int	ft_execute_sys_bin(t_store *store, t_cmd *cmd)
{
	if (!cmd->value && cmd->value[0] == '\0')
		return (EXIT_CMD_NOT_FOUND);
	if (ft_command_is_dir(cmd->value))
		return (EXIT_CMD_NOT_FOUND);
	cmd->path = ft_parser_path(store, cmd->value);
	if (!cmd->path)
		return (EXIT_CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, store->envp) == -1)
		ft_error_handler("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	ft_execute_local_bin(t_store *data, t_cmd *cmd)
{
	int	res;

	if (ft_strchr(cmd->value, '<') != NULL || ft_strchr(cmd->value,
			'>') != NULL)
		return (EXIT_SUCCESS);
	res = ft_check_command_not_found(data, cmd);
	if (res != 0)
		return (res);
	if (execve(cmd->value, cmd->args, data->envp) == -1)
		return (ft_error_handler("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

/*
 *	Child process tries to execute the given command by setting
 *	its input/output fds and searching for an executable.
 *	Searching for executable in this order:
 *		1. Execute builtin command
 *		2. Execute system binaries for command.
 *		3. Execute given command name directly (local bin)
 *	If it cannot find a matching builtin or executable,
 *	prints an error message.
 *	Child exits with it's executed program's exit code, or 1 if
 *	it could not find one.
 */
int	ft_execute_command(t_store *store, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (!cmd || !cmd->value)
		ft_exit_program(store, ft_error_handler("child", NULL,
				"parsing error: command not found", EXIT_FAILURE));
	if (!ft_check_io(cmd->redirect))
		ft_exit_program(store, EXIT_FAILURE);
	ft_set_pipe_fds(store->pars, cmd);
	ft_redirect_io(cmd->redirect);
	ft_close_fds(store->pars, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(cmd->value, '/') == NULL)
	{
		exit_code = ft_execute_builtin(store, cmd);
		if (exit_code != EXIT_CMD_NOT_FOUND)
			ft_close_executer(exit_code, store);
		exit_code = ft_execute_sys_bin(store, cmd);
		if (exit_code != EXIT_CMD_NOT_FOUND)
			ft_close_executer(exit_code, store);
	}
	exit_code = ft_execute_local_bin(store, cmd);
	ft_close_executer(exit_code, store);
	return (exit_code);
}
