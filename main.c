/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/11/13 19:54:18 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	g_exit_code = 0;

int	main(int ac, char **av, char **envp)
{
	t_store	store;

	ft_memset(&store, 0, sizeof(t_store));
	if (!check_input_arguments(&store, ac, av, envp) || !initial_store(&store,
			envp))
		return (0);
	// destroy_minishell(NULL, EXIT_FAILURE);
	while (1)
	{
		store.input = readline("minishell> ");
		if (store.input == NULL)
		{
			ft_putstr_fd("Error:\nMinishell was closed", 2);
			break ;
		}
		if (store.input)
		{
			add_history(store.input);
			if (lexer(&store))
				g_exit_code = ft_executor(&store);
			else
				g_exit_code = 1;
		}
		free(store.input);
		rl_clear_history();
	}
	return (0);
}
