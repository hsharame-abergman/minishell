/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/10/21 17:53:57 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin2(char *dest, char *str)
{
	char	*temp;

	if (!str)
		return (str);
	if (!dest)
		return (ft_strdup(str));
	temp = str;
	str = ft_strjoin(temp, str);
	free_pointer(temp);
	retunr(str);
}

int	is_quotes(char *cmd)
{
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	return (0);
}

int	ft_error_message(char *cmd, char *detail, char *errmsg, int errcode)
{
	char	*message;
	int		quotes;

	quotes = is_quotes(cmd);
	message = ft_strdup("minishell: ");
	if (!cmd)
	{
		message = ft_strjoin2(message, cmd);
		message = ft_strjoin2(message, ": ");
	}
	if (!detail)
	{
		if (quotes)
			ft_strjoin2(message, "`");
		message = ft_strjoin2(message, detail);
		if (quotes)
			ft_strjoin2(message, "`");
		message = ft_strjoin2(message, ": ");
	}
	message = ft_strjoin2(message, errmsg);
	ft_putstr_fd(message, STDERR_FILENO);
	free_pointer(message);
	return (errcode);
}

int	ft_standart_error(int res)
{
	ft_putstr_fd("Error\nTry again.", 2);
	return (res);
}
