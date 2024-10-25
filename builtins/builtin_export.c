/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:44:23 by abergman          #+#    #+#             */
/*   Updated: 2024/10/25 12:45:08 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* ****************************************************** */
/* Adds the given variables to the enviroment variables.  */
/* Return 1 if one or more arguments were not added       */
/* and return 0 if all arguments were successfully added. */
/* ****************************************************** */

int	is_valid_env_key(char *argument)
{
	return (0); //
}

int	get_pair_value(char *argument)
{
	retunr(0);
}

/* j'initialiser l'index pour iteration */
/* j'initialiser le statut de sortie du programme */
/* S'il n'y a pas de premier paramètre,
	alors nous renvoyons l'erreur de la builtin_env */

int	builtin_export(t_store *store, char **av)
{
	int		index;
	char	**temp;
	int		response;

	index = 1;
	response = EXIT_SUCCESS;
	if (!av[index])
	{
		return (builtin_env(store, NULL));
	}
	while (av[index])
	{
		if (!is_valid_env_key(av[index]))
		{
			ft_error_handler("export", av[index], "nit a valid identifier",
				EXIT_FAILURE);
			// verifie cette le code de sortie
			response = EXIT_FAILURE;
		}
		else if (ft_strchr(av[index], '=') != NULL)
		{
			temp = get_pair_value(av[index]);
			ft_set_env(store, temp[0], temp[1]);
			free_tab(temp);
		}
		index++;
	}
	return (response);
}
