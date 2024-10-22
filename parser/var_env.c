/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:04:51 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/22 12:09:31 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	check_var(t_cmd *cmd)
{
	while (cmd && cmd->left)
	{
		if (ft_strcmp(cmd->value, "echo"))
			find_var(cmd);
		cmd = cmd->left;
	}
}
