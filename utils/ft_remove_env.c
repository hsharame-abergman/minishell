/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:49:12 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:25:55 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char	**ft_realloc_envs(t_store *store, int counter)
{
	char	**new_envs;
	int		i;

	i = 0;
	new_envs = malloc(sizeof(char *) * (counter + 1));
	if (new_envs == NULL)
		return (NULL);
	while (i < counter)
	{
		new_envs[i] = ft_strdup(store->envp[i]);
		i++;
	}
	new_envs[i] = NULL;
	return (new_envs);
}

int	ft_remove_env(t_store *store, int index)
{
	int	counter;
	int	i;

	if (index > ft_count_env(store->envp))
		return (0);
	ft_free_pointer(store->envp[index]);
	i = index;
	counter = index;
	while (store->envp[i + 1])
	{
		store->envp[i] = store->envp[i + 1];
		ft_free_pointer(store->envp[i + 1]);
		counter++;
		i++;
	}
	store->envp = ft_realloc_envs(store, counter);
	if (!store->envp)
		return (0);
	return (1);
}
