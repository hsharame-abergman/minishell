/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:35 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/15 21:18:32 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	*parser_pipe(t_token *token, t_ast *last)
{
	t_ast	*current;

	if (!last)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	current = create_node(token->value, NODE_PIPE);
	last->right = current;
	current->left = last;
	return (current);
}

t_ast	*parser_redirect(t_token **token, t_ast *last)
{
	t_ast	*current;
	int		type;

	type = get_pars_type((*token)->value, (*token)->type);
	current = create_node((*token)->value, type);
	if (last)
	{
		last->right = current;
		current->left = last;
	}
	(*token) = (*token)->next;
	current->right = parser_cmd(*token, current);
	if (current->right->value[0] == '\n')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (NULL);
	}
	return (current);
}
