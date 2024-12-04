/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command_not_found.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:12 by abergman          #+#    #+#             */
/*   Updated: 2024/12/04 18:46:46 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_check_command_not_found(t_store *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->value, '/') == NULL && ft_get_env_index(data->envp,
			"PATH") != -1)
		return (ft_error_handler(cmd->value, NULL, "command not found",
				EXIT_CMD_NOT_FOUND));
	if (access(cmd->value, F_OK) != 0)
		return (ft_error_handler(cmd->value, NULL, strerror(errno),
				EXIT_CMD_NOT_FOUND));
	else if (ft_command_is_dir(cmd->value))
		return (ft_error_handler(cmd->value, NULL, "is a directory",
				EXIT_CMD_NOT_EXECUT));
	else if (access(cmd->value, F_OK | X_OK) != 0)
		return (ft_error_handler(cmd->value, NULL, strerror(errno),
				EXIT_CMD_NOT_EXECUT));
	return (EXIT_SUCCESS);
}
