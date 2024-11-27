/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_valid_command_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:10:00 by abergman          #+#    #+#             */
/*   Updated: 2024/11/27 16:32:28 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Check access and permissions for each possible command to find a valid
	path to binary files for a cmd.
if the valid path not found - return NULL */
char	*ft_find_valid_command_path(char *command, char **paths)
{
	int		index;
	char	*command_path;

	index = 0;
	command_path = NULL;
	while (paths[index])
	{
		command_path = ft_strjoin(paths[index], command);
		if (!command_path)
		{
			ft_error_handler("malloc", NULL, "an unexpected error ocured",
				EXIT_FAILURE);
			return (NULL);
		}
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		ft_free_pointer(command_path);
		index++;
	}
	return (NULL);
}
