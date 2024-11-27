/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/27 16:05:32 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int		g_exit_code = 0;

void	ft_monitor_singleline(t_store *store, char **args)
{
	char	**commands;
	int		index;

	index = 0;
	commands = ft_split(args[2], ';');
	if (!commands)
		ft_exit_program(store, EXIT_FAILURE);
	while (commands[index])
	{
		store->input = ft_strdup(commands[index]);
		if (lexer(store))
			g_exit_code = ft_executor(store);
		else if (g_exit_code == 0)
			g_exit_code = 1;
		add_history(store->input);
		index++;
	}
}

void	ft_ctrl_d_handler(t_store *store)
{
	ft_putendl_fd(B_EXIT, 2);
	ft_free_store(store, 1);
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
		if (!store->input)
			ft_ctrl_d_handler(store);
		free(label);
		label = NULL;
		if (store->input && store->input[0] != '\0')
		{
			if (lexer(store))
				g_exit_code = ft_executor(store);
			else if (g_exit_code == 0)
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
	if (st.mode_usage == SINDLE_COMMAND)
		ft_monitor_singleline(&st, av);
	else
		ft_monitor(&st);
	ft_exit_program(&st, g_exit_code);
	return (0);
}
