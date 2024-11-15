/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_store.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:03:12 by abergman          #+#    #+#             */
/*   Updated: 2024/11/15 15:51:14 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	initial_envp(t_store *store, char **envp)
{
	int	index;

	store->envp = ft_calloc(ft_count_env(envp) + 1, sizeof(store->envp));
	if (!store->envp)
		return (0);
	index = 0;
	while (envp[index])
	{
		store->envp[index] = ft_strdup(envp[index]);
		if (!store->envp[index])
			return (0);
		index++;
	}
	return (1);
}

static int	initial_working_dir_vars(t_store *store)
{
	(void)store;
	return (1);
}

int	initial_store(t_store *store, char **envp)
{
	if (!initial_envp(store, envp))
		return (ft_putstr_fd("TODO: Create error message", 2), 1);
	if (!initial_working_dir_vars(store))
		return (ft_putstr_fd("TODO: Create error message", 2), 1);
	store->token = NULL;
	store->input = NULL;
	return (1);
}
