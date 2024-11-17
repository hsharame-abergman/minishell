/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:25:37 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/16 20:34:16 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->redirect)
		{
			close(cmds->fd_pipe[0]);
			close(cmds->fd_pipe[1]);
		}
		cmds = cmds->right;
	}
}

int	ft_set_pipe_fds(t_cmd *cmds, t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->left && cmd->left->pipe)
		dup2(cmd->left->fd_pipe[0], STDIN_FILENO);
	if (cmd->pipe)
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
	ft_close_pipe_fds(cmds, cmd);
	return (1);
}
