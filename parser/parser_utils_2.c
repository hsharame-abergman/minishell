/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:03:14 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/22 18:30:51 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	check_if_exists(t_cmd *node)
{
	if (node->value && node->path == NULL)
		cmd_error(node, 1);
	else
	{
		if (!access(node->value, F_OK))
			cmd_error(node, 2);
		else if (!access(node->value, X_OK))
			cmd_error(node, 3);
	}
}

void	cmd_error(t_cmd *node, int i)
{
	node->error = true;
	if (i == 1)
		printf("minishell: %s: command not found\n", node->value);
	else if (i == 2)
		printf("minishell: %s: No such file or directory\n", node->value);
	else if (i == 3)
		printf("minishell: %s: Permission denied\n", node->value);
	exit ;
}
