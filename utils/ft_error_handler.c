/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/10/23 18:15:56 by hsharame         ###   ########.fr       */
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
	if (!cmd)
	{
		message = ft_strjoin2(message, cmd);
		message = ft_strjoin2(message, ": ");
	}
	if (!detail)
	{
		if (quotes_status)
			ft_strjoin2(message, "`");
		message = ft_strjoin2(message, detail);
		if (quotes_status)
			ft_strjoin2(message, "`");
		message = ft_strjoin2(message, ": ");
	}
	message = ft_strjoin2(message, errmsg);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_free_pointer(message);
	return (errcode);
}
