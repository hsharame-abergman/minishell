/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:51:16 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:53:58 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
Restores the original default input and output to the original values 0 and 1
	Used to delete input/output values after execution 
	as preparation for the next set of user commands.
	Returns 1 if the copy was successful, 0 if not.
*/
int	ft_restore_io(t_redirect *redirect)
{
	int	response;

	response = 1;
	if (!redirect)
		return (response);
	if (redirect->stdin_backup != -1)
	{
		if (dup2(redirect->stdin_backup, STDIN_FILENO) == -1)
			response = 0;
		close(redirect->stdin_backup);
		redirect->stdin_backup = -1;
	}
	if (redirect->stdout_backup != -1)
	{
		if (dup2(redirect->stdout_backup, STDOUT_FILENO) == -1)
			response = 0;
		close(redirect->stdout_backup);
		redirect->stdout_backup = -1;
	}
	return (response);
}
