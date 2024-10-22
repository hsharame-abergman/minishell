/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:03:14 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/22 16:15:14 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	check_if_exists(t_cmd *node)
{
	if (node->path == NULL)
		cmd_error(node);
	else
	{
		
	}
}

void	cmd_error(t_cmd *node)
{
	node->error = true;
	printf("minishell: %s:command not found\n", node->value);
	exit ;
}
