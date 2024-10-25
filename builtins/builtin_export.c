/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:44:23 by abergman          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:47 by abergman         ###   ########.fr       */
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

static char	**ft_separate_values(char *argument)
{
	char	**response;
	char	**node;

	node = ft_strchr(argument, '=');
	response = malloc(sizeof *response * (2 + 1));
	response[0] = ft_substr(argument, 0, node - argument);
	response[1] = ft_substr(node, 1, ft_strlen(node));
	response[2] = NULL;
	return (response);
}

/* j'initialiser l'index pour iteration                  */
/* j'initialiser le statut de sortie du programme        */
/* S'il n'y a pas de premier paramètre,                  */
/* alors nous renvoyons l'erreur de la builtin_env       */

int	builtin_export(t_store *store, char **av)
{
	int		index;
	char	**node;
	int		response;

	index = 1;
	response = EXIT_SUCCESS;
	if (!av[index])
		return (builtin_env(store, NULL));
	while (av[index])
	{
		if (!is_valid_env_key(av[index]))
		{
			ft_error_handler("export", av[index], "nicht a valid identifier", 0);
			response = EXIT_FAILURE;
		}
		else if (ft_strchr(av[index], '=') != NULL)
		{
			node = ft_separate_values(av[index]);
			ft_set_env(store, node[0], node[1]);
			free_tab(node);
		}
		index++;
	}
	return (response);
}
