/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/21 15:56:09 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header/minishell.h"

int		g_exit_code = 0;

void	ft_monitor(t_store *store)
{
	char	*label;

	while (1)
	{
		// ft_set_signals_interactive();
		label = ft_create_label_for_readline(store);
		store->input = readline(label);
		if (store->input && store->input[0] != '\0')
		{
			if (check_input(store->input))
			{
				if (lexer(store))
					g_exit_code = ft_executor(store);
				else
					g_exit_code = 1;
			}			
			add_history(store->input);
		}
		free(label);
		ft_free_store(store, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_store	st;

	ft_memset(&st, 0, sizeof(t_store));
	if (!ft_check_args(&st, ac, av, env) || !ft_init_store(&st, env))
		return (0);
	ascii_welcome();
	ft_monitor(&st);
	ft_exit_program(&st, g_exit_code);
	return (0);
}
