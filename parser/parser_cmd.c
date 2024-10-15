/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/15 22:10:09 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	*parser_cmd(t_token *token, t_ast *last)
{
	t_ast	*current;
	int		type;

	type = get_pars_type(token->value, token->type);
	current = create_node(token->value, type);
	if (current->type == FLAG && !last)
	{
		ft_putstr_fd("-n: command not found\n", 2);
		return (NULL);
	}
	if (last)
	{
		if (last->type != CMD && current->type == FLAG)
			current->type = ARGUMENT;
		last->right = current;
		current->left = last;
	}
		return (current);
}
