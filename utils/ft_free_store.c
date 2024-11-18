/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_store.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:51 by abergman          #+#    #+#             */
/*   Updated: 2024/11/18 18:08:04 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	handle_bracket(t_store *data, char *str)
{
	(void)data;
	printf("minishell: syntax error near unexpected token '%s'\n", str);
}

bool	check_bracket(t_store *data)
{
	char	*bracket;

	bracket = ft_strchr(data->input, '(');
	if (bracket != NULL)
	{
		handle_bracket(data, bracket);
		return (true);
	}
	bracket = ft_strchr(data->input, ')');
	if (bracket != NULL)
	{
		handle_bracket(data, bracket);
		return (true);
	}
	return (false);
}

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
	if (store && store->token)
		free_token(&store->token);
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
