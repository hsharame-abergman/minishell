/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:34:37 by abergman          #+#    #+#             */
/*   Updated: 2024/12/04 19:01:20 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int		g_exit_code = 0;

void	ft_ctrl_d_handler(t_store *store)
{
	ft_putendl_fd(B_EXIT, 2);
	ft_exit_program(store, g_exit_code);
}

void	ft_monitor(t_store *store)
{
	char	*label;

	while (1)
	{
		ft_set_signals_interactive();
		label = ft_create_label_for_readline(store);
		store->input = readline(label);
		free(label);
		label = NULL;
		if (!store->input)
			return (ft_ctrl_d_handler(store));
		if (store->input && store->input[0] != '\0')
		{
			if (lexer(store))
				g_exit_code = ft_executor(store);
			else if (g_exit_code == 0 && !void_input(store))
				g_exit_code = 1;
			add_history(store->input);
		}
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
