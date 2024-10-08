/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/10/08 11:33:00 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_tiny tiny;

	(void)ac;
	(void)av;

	if (ac != 1 || envp == NULL || *envp == NULL)
		return (ft_putstr_fd("Error:\nNo environment found. Exiting.", 1), 0);
	init(&tiny, envp);
	while (tiny.exit == 0)
	{
		ft_putstr_fd("minishell> ", 1);
		input = readline(NULL);
		if (input == NULL)
		{
			ft_putstr_fd("Error:\nMinishell was closed", 1);
			break ;
		}
		if (*input)
		{
			add_history(input);
		}
		free(input);
	}
	return (0);
}
