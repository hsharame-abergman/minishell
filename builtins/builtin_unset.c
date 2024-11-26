/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:46:28 by abergman          #+#    #+#             */
/*   Updated: 2024/11/26 16:52:06 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	builtin_unset(t_store *store, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (!av)
		return (EXIT_SUCCESS);
	while (av[i])
	{
		j = ft_get_env_index(store->envp, av[i]);
		if (j != -1)
		{
			ft_remove_env(store, j);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
