/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:27 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:53:31 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
   Search for this variable in environment variables.
   Returns the pointer to the value of a variable in the environment
   matches the string. Partial variable names are not
   supported: the specified string must be a full variable name.
   Returns NULL if the string cannot be found in the environment.
*/
char	*ft_get_env_value(char **envp, char *search)
{
	int		index;
	char	*node;

	node = ft_strjoin(search, "=");
	if (!node)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(node, envp[index], ft_strlen(node)) == 0)
		{
			ft_free_pointer(node);
			return (ft_strchr(envp[index], '=') + 1);
		}
		index++;
	}
	ft_free_pointer(node);
	return (NULL);
}

/*
	Search for this variable in environment variables.

	Returns the index of the variable in the environment
	matches the string. Partial variable names are not
	supported: the specified string must be a full variable name.
	Returns -1 if the string cannot be found in the surrounding.
*/
int	ft_get_env_index(char **envp, char *key)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strjoin(key, "=");
	if (!res)
		return (-1);
	while (envp[i])
	{
		if (ft_strncmp(res, envp[i], ft_strlen(res)) == 0)
		{
			ft_free_pointer(res);
			return (i);
		}
		i++;
	}
	ft_free_pointer(res);
	return (-1);
}
