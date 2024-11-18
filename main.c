/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/11/18 19:30:45 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int		g_exit_code = 0;

int	main(int ac, char **av, char **envp)
{
	t_store	store;
	char	*label;

	ft_memset(&store, 0, sizeof(t_store));
	if (!ft_check_input_args(&store, ac, av, envp) || !initial_store(&store,
			envp))
		return (0);
	ascii_welcome();
	while (1)
	{
		ft_set_signals_interactive();
		label = ft_create_label_for_readline(envp, &store);
		store.input = readline(label);
		if (store.input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (store.input && store.input[0] != '\0')
		{
			add_history(store.input);
			if (lexer(&store))
				g_exit_code = ft_executor(&store);
			else
				g_exit_code = 1;
		}
		// ft_free_store(&store, 1);
	}
	rl_clear_history();
	free(label);
	ft_exit_program(&store, g_exit_code);
	return (0);
}
