/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:03:36 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/25 16:03:40 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
 *	Closes opened file descriptors, including pipes and input and
 *	output fds.
 *   If close_backups is set to true, it also closes
 *	backup STDIN and STDOUT file descriptors.
 */
void	ft_close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds->redirect)
	{
		if (cmds->redirect->fd_in != -1)
			close(cmds->redirect->fd_in);
		if (cmds->redirect->fd_out != -1)
			close(cmds->redirect->fd_out);
		if (close_backups)
			ft_restore_io(cmds->redirect);
	}
	ft_close_pipe_fds(cmds, NULL);
}
