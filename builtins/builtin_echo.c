/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:46:04 by abergman          #+#    #+#             */
/*   Updated: 2024/11/26 16:48:44 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* ***************************************************** */
/* Imprime le tableau donné (value) d'arguments à STDOUT */

static void	ft_echo_util(char **av, int is_newline, int index)
{
	int	ii;

	ii = 0;
	if (!av[index])
	{
		if (!is_newline)
			ft_putchar_fd('\n', STDERR_FILENO);
		return ;
	}
	while (av[index])
	{
		while (av[index][ii])
		{
			if ((int)(av[index][ii]) == 92)
				ii++;
			ft_putchar_fd(av[index][ii], STDOUT_FILENO);
			ii++;
		}
		if (av[index + 1])
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		else if (!av[index + 1] && !is_newline)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		index++;
	}
}

/* **************************************************************** */
/* Imprime les chaînes données et ajoute une nouvelle ligne ou non, */
/* 	selon le flag -n.                                               */

int	builtin_echo(char **av)
{
	int	index;
	int	is_n;

	index = 1;
	is_n = 0;
	if (!av)
		return (ft_putchar_fd('\n', 1), EXIT_SUCCESS);
	while (av[index] && ft_search_flag(av[index], 'n'))
	{
		is_n = 1;
		index++;
	}
	ft_echo_util(av, is_n, index);
	return (EXIT_SUCCESS);
}
