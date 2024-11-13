/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths_from_envp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:44:59 by abergman          #+#    #+#             */
/*   Updated: 2024/11/13 19:37:29 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Attempts to extract paths from the PATH enviroment variable. */
char	**ft_get_paths_from_envp(t_store *store)
{
	char	**envp_paths;

	if (ft_get_env_index(store->envp, "PATH") == -1)
		return (NULL);
	envp_paths = ft_split(ft_get_env_value(store->envp, "PATH"), ':');
	if (!envp_paths)
		return (NULL);
	return (envp_paths);
}
