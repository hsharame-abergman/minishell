/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/11/21 15:33:45 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ft_verify_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	return (0);
}

int	ft_error_handler(char *cmd, char *detail, char *errmsg, int errcode)
{
	char	*message;
	int		quotes_status;

	quotes_status = ft_verify_quotes(cmd);
	message = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		message = ft_strjoin(message, cmd);
		message = ft_strjoin(message, ": ");
	}
	if (detail != NULL)
	{
		if (quotes_status)
			ft_strjoin(message, "`");
		message = ft_strjoin(message, detail);
		if (quotes_status)
			ft_strjoin(message, "`");
		message = ft_strjoin(message, ": ");
	}
	message = ft_strjoin(message, errmsg);
	ft_putendl_fd(message, STDERR_FILENO);
	ft_free_pointer(message);
	return (errcode);
}
