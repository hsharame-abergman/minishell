/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_store.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:51 by abergman          #+#    #+#             */
/*   Updated: 2024/11/11 15:27:25 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				ft_free_pointer(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	ft_free_store(t_store *store, int history)
{
	if (store && store->input)
	{
		ft_free_pointer(store->input);
		store->input = NULL;
	}
	if (history)
	{
		if (store && store->working_directory)
			ft_free_pointer(store->working_directory);
		if (store && store->old_working_directory)
			ft_free_pointer(store->old_working_directory);
		if (store && store->envp)
			ft_free_str_tab(store->envp);
		rl_clear_history();
	}
}
