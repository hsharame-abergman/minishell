/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_is_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:56:54 by abergman          #+#    #+#             */
/*   Updated: 2024/10/28 12:42:25 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* ********************************************************************* */
/* Checks is the kay is a valid name for an enviroment variable.         */
/* Returns 1 if the key contain only alphabetic or numeric chars of "_"  */

int	ft_env_is_valid(char *node)
{
	int	index;

	index = 0;
	if (ft_isalpha(node[index]) == 0 && node[index] != '_')
	{
		return (0);
	}
	index++;
	while (node[index] && node[index] != '=')
	{
		if (ft_isalnum(node[index]) != 1 && node[index] != '_')
		{
			return (0);
		}
		index++;
	}
	return (1);
}
