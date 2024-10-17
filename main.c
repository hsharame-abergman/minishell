/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/10/17 13:41:43 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_store *data;

	(void)ac;
	(void)av;
	if (ac != 1 || envp == NULL || *envp == NULL)
		return (ft_putstr_fd("Error:\nNo environment found. Exiting.", 2), 0);
	data = builtins(av);
	// init(&tiny, envp);
	while (1)
	{
		ft_putstr_fd("minishell> ", 1);
		data->input = readline(NULL);
		if (data->input == NULL)
		{
			ft_putstr_fd("Error:\nMinishell was closed", 2);
			break ;
		}
		if (data->input)
		{
			add_history(data->input);
			if (lexer(data))
				// g_exit_code = builtin();
			else
				g_exit_code = 1;
		}
		free(data->input);
		//rl_clear_history();
	}
	return (0);
}
