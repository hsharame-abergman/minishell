/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:20 by abergman          #+#    #+#             */
/*   Updated: 2024/11/19 15:48:23 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* ************************************************************************ */
/* Executes given commands by creating child processes and waiting			*/
/* for them to finish. Returns the exit code of the last child to finish.	*/
/* Returns exit code 1 if creating a child process fails. 					*/
int	ft_redirect_io(t_redirect *redirect)
{
	int response;

	response = 1;
	if (!redirect)
		return (0);
	redirect->stdin_backup = dup(STDIN_FILENO);
	if (redirect->stdin_backup == -1)
		response = ft_error_handler("dup", "stdin backup", strerror(errno), 1);
	if (redirect->stdout_backup == -1)
		response = ft_error_handler("dup", "stdout backup", strerror(errno), 1);
	if (redirect->fd_in != -1)
		if (dup2(redirect->fd_in, STDIN_FILENO) == -1)
			response = ft_error_handler("dup2", redirect->infile,
					strerror(errno), 1);
	if (redirect->fd_out != -1)
		if (dup2(redirect->fd_out, STDOUT_FILENO) == -1)
			response = ft_error_handler("dup2", redirect->outfile,
					strerror(errno), 1);
	return (response);
}
