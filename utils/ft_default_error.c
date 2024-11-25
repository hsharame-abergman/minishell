/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/11/25 13:26:58 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_defauit_error(int res)
{
	ft_putstr_fd("Error\nTry again.", 2);
	return (res);
}

int	error_syntax(char *s, int error, bool code)
{
	char	*str;

	if (code)
		g_exit_code = EXIT_GENERAL_ERROR;
	str = ft_strjoin("minishell: ", s);
	ft_putstr_fd(str, 2);
	free(str);
	return (error);
}
