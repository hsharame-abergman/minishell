/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:51:16 by abergman          #+#    #+#             */
/*   Updated: 2024/11/27 16:34:35 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Восстанавливает исходный стандартный вход и выход до исходных значений 0 и 1
	Используется для удаления входных/выходных значений после выполнения 
	в качестве подготовки к следующему набору команд пользователя.
	Возвращает 1, если копирование было успешным, 0, если нет.
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
		redirect->stdout_backup = -1;
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
