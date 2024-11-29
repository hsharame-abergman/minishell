/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:44:23 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:44:36 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Adds the given variables to the enviroment variables.  */
/* Return 1 if one or more arguments were not added       */
/* and return 0 if all arguments were successfully added. */
int	is_valid_env_key(char *argument)
{
	int	index;

	index = 0;
	if (ft_isalpha(argument[index]) == 0 && argument[index] != '_')
		return (1);
	index++;
	while (argument[index] && argument[index] != '=')
	{
		if (ft_isalnum(argument[index]) == 0 && argument[index] != '_')
			return (1);
		index++;
	}
	return (0);
}

/* Divides the argument into a value-key pair for the environment variable. */
/* Returns a 2-line array, containing the key and value  */
/* 	of the new environment variable. */
/* Returns NULL in case of error. */
static char	**ft_separate_values(char *argument)
{
	char	**response;
	char	*node;

	node = ft_strchr(argument, '=');
	response = malloc(sizeof(*response) * (2 + 1));
	response[0] = ft_substr(argument, 0, node - argument);
	response[1] = ft_substr(node, 1, ft_strlen(node));
	response[2] = NULL;
	return (response);
}

/* i initialize the index for iteration					*/
/* I initialize the program exit status   				*/
/* If there is no first parameter,           	        */
/* then we return the error of builtin_env				*/
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
		if (is_valid_env_key(av[index]))
		{
			ft_error_handler("export", av[index], "not a valid identifier", 0);
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
