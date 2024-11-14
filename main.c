/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/11/14 17:48:38 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int		g_exit_code = 0;

int	main(int ac, char **av, char **envp)
{
	t_store	store;
	char	*label;

	ft_memset(&store, 0, sizeof(t_store));
	if (!check_input_arguments(&store, ac, av, envp) || !initial_store(&store,
			envp))
		return (0);
	ascii_welcome();
	label = ft_create_label_for_readline(envp);
	while (1)
	{
		store.input = readline(label);
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
	free(label);
	return (0);
}
