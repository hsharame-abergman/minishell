/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:25:37 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/29 11:25:53 by hsharame         ###   ########.fr       */
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
