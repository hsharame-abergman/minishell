/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:33:18 by abergman          #+#    #+#             */
/*   Updated: 2024/10/07 19:15:39 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		ft_putstr_fd("minishell> ", 1);
		input = readline(NULL);
		if (input == NULL)
		{
			ft_putstr_fd("\nMinishell was closed", 1);
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
