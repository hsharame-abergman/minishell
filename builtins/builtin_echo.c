/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:46:04 by abergman          #+#    #+#             */
/*   Updated: 2024/10/14 16:52:29 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	builtin_echo(char **av)
{
	int	index;
	int	is_newline;

	index = 1;
	is_newline = 0;
	if (av[1] != NULL && ft_strcmp(av[1], "-n") == 0)
	{
		is_newline = 0;
		index = 2;
	}
	while (av[index])
	{
		printf("%s", av[index]);
		if (av[index + 1] != NULL)
			printf(" ");
		index++;
	}

	if (is_newline)
	{
		printf("\n");
	}
}
