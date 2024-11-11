/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:41:52 by abergman          #+#    #+#             */
/*   Updated: 2024/11/11 15:27:01 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
Проверяет, правильно ли настроены инфайл и outfile.
	Возвращает 1 при успехе, 0 при неудаче.
*/
int	ft_check_io(t_redirect *redirect)
{
	if (!redirect || (!redirect->infile && !redirect->outfile))
		return (1);
	if ((redirect->infile && redirect->fd_in == -1) || (redirect->outfile
			&& redirect->fd_out == -1))
		return (0);
	return (1);
}
