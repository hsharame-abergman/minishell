/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:35 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/14 17:32:29 by hsharame         ###   ########.fr       */
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
	current = create_node("|", NODE_PIPE);
	current->left = last;
	return (current);
}
