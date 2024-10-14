/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:29 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/14 17:48:04 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	*parser_redirect(t_token *token, t_ast *last)
{
	t_ast	*current;

	//current = create_node("<", get_pars_type);
	if (last)
		current->left = last;
	token = token->next;
	current->right = parser_cmd(token, current);
	if (current->right->value[0] == '\n')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (NULL);
	}
	return (current);
}
