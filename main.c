/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/10/16 22:58:43 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

global int errcode;

int	main(int ac, char **av, char **envp)
{
	t_minishell *data;
	char	*input;

	(void)ac;
	(void)av;

	if (ac != 1 || envp == NULL || *envp == NULL)
		return (ft_putstr_fd("Error:\nNo environment found. Exiting.", 2), 0);
	data = builtins(av);
	// init(&tiny, envp);
	while (1)
	{
		ft_putstr_fd("minishell> ", 1);
		input = readline(NULL);
		if (input == NULL)
		{
			ft_putstr_fd("Error:\nMinishell was closed", 2);
			break ;
		}
		if (*input)
		{
			// add_history(input);
			lexer(input);
			// builtin();
		}
		free(input);
		//rl_clear_history();
	}
	return (0);
}
