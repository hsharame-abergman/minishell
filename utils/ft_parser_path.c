/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:14:28 by abergman          #+#    #+#             */
/*   Updated: 2024/11/12 21:27:28 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Searches env PATH for location of given command's bin file */

char *ft_parser_path(t_store *store, t_cmd *value)
{
	char **path_of_envariment;
	char *command;
	char *path_of_command;

	// if (!value)
		// return (NULL);
	
	path_of_envariment = ft_get_paths_from_evnp(store);
	if (!path_of_envariment)
		return (NULL);
	command = ft_strjoin("/", value);
	if (!command)
	{
		ft_free_tab(path_of_envariment);
		return (NULL);
	}
	path_of_command = ft_find_valid_command_path(command, path_of_envariment);
	if (!path_of_command)
	{
		ft_free_pointer(command);
		ft_free_tab(path_of_envariment);
		return (NULL);
	}
	return (path_of_command);
}
