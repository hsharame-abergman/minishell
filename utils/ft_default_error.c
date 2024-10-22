/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/10/22 16:26:50 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_defauit_error(int res)
{
	ft_putstr_fd("Error\nTry again.", 2);
	return (res);
}

int	error_syntax(char *s, int error)
{
	char	*str;

	str = ft_strjoin("minishell: ", s);
	ft_putstr_fd(str, 2);
	free(str);
	return (error);
}
