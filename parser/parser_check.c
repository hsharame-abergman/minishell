/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:29 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/18 17:07:33 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	check_cmd(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		current = current->right;
	}
	return (true);
}

bool	check_grammar(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (!current->value[0] == '|')
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (false);
		}
		current = current->right;
	}
	return (true);
}
