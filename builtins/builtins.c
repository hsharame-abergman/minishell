/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/14 17:13:41 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int ac, char **av, char **env)
{
	if (is_builtins(av))
	{
		if (ft_strcmp(av[0], "echo") == 0)
			builtin_echo(av);
		else if (ft_strcmp(av[0], "cd") == 0)
			builtin_cd(av);
	}
	return (0);
}
