/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:47:52 by abergman          #+#    #+#             */
/*   Updated: 2024/11/05 12:00:19 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int builtin_env(t_store *store, char **av)
{
	int res;

	if (av && av[1])
		return (ft_error_handler("env", NULL, "too many arguments", 2));
	res = 0;
	if (!store->envp)
		return (EXIT_FAILURE);
	while (store->envp[res])
	{
		ft_putendl_fd(store->envp[res], STDOUT_FILENO);
		res++;
	}
	return (EXIT_SUCCESS);
}
