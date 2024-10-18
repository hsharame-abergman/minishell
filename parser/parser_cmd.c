/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/18 15:52:58 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*parser_cmd(t_token *token, t_cmd *last)
{
	t_cmd	*current;

	current = create_node(token->value);
	if (last)
	{
		last->right = current;
		current->left = last;
	}
	return (current);
}

t_cmd	*handle_command(t_token **save, t_cmd **last_node, int *first)
{
	t_cmd	*current;

	current = parser_cmd(*save, *last_node);
	*first = 0;
	*save = (*save)->next;
	return (current);
}

void	handle_pipe(t_token **save, t_cmd **current, int *first)
{
	(*current)->pipe = true;
	*save = (*save)->next;
	*first = 1;
}
