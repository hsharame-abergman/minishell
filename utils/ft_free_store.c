/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_store.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:51 by abergman          #+#    #+#             */
/*   Updated: 2024/12/04 18:07:14 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	check_bracket(char *str)
{
	int		i;
	bool	in_quote;

	i = 0;
	in_quote = false;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"'))
			in_quote = !in_quote;
		if (!in_quote)
		{
			if (str[i] == '(' || str[i] == ')')
			{
				printf("minishell: syntax error near unexpected token '%c'\n",
					str[i]);
				return (false);
			}
		}
		i++;
	}
	return (true);
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
		ft_free_pointer(store->input);
	if (store && store->token)
		free_token(&store->token);
	if (store && store->pars)
		free_cmd(&store->pars);
	if (history)
	{
		rl_clear_history();
		if (store && store->working_directory)
			ft_free_pointer(store->working_directory);
		if (store && store->old_working_directory)
			ft_free_pointer(store->old_working_directory);
		if (store && store->envp)
			ft_free_str_tab(store->envp);
	}
}
