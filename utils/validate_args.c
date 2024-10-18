/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:08:21 by abergman          #+#    #+#             */
/*   Updated: 2024/10/18 17:09:23 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_input_arguments(t_store *store, int ac, char *av, char **envp)
{
	if (envp == NULL || *envp == NULL)
		return (ft_putstr_fd("Error:\nNo environment found. Exiting.", 2), 0);
	if ((ac != 1 && ac != 3))
		return (ft_putstr_fd("Error:\nThe arguments is not valid.", 2), 0);
	if (ac == 3)
	{
		store->mode_usage = SINDLE_COMMAND;
		if (!av[1] || (av[1] && ft_strcmp(av[1], "-c") != 0))
			return (ft_putstr_fd("Error:\nFirst argument not found.", 2), 0);
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (ft_putstr_fd("Error:\nSecond argument not valid.", 2), 0);
	}
	else
		store->mode_usage = INTERACTIVE;
	return (1);
}
