/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/11/27 14:22:30 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_error_handler(char *cmd, char *detail, char *errmsg, int errcode)
{
	char	*message[2];

	message[0] = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		message[1] = ft_strjoin_free(message[0], cmd, FREE_DEST);
		message[0] = ft_strjoin_free(message[1], ": ", FREE_DEST);
	}
	if (detail != NULL)
	{
		message[1] = ft_strjoin_free(message[0], detail, FREE_DEST);
		message[0] = ft_strjoin_free(message[1], ": ", FREE_DEST);
	}
	message[1] = ft_strjoin_free(message[0], errmsg, FREE_DEST);
	ft_putendl_fd(message[1], STDERR_FILENO);
	ft_free_pointer(message[1]);
	return (errcode);
}
