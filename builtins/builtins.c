/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/14 17:40:05 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_minishell	*main(int ac, char **av, char **env)
{
	t_minishell	*data;

	if (is_builtins(av))
	{
		if (ft_strcmp(av[0], "echo") == 0)
			builtin_echo(av);
		else if (ft_strcmp(av[0], "cd") == 0)
			builtin_cd(av);
	}
	return (data);
}
