/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:50:50 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/11 15:58:41 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	*init_tree(t_token **token_list)
{
	t_token	*save;
	t_ast	*node;

	save = *token_list;
	node = parser_pipe(token_list);
	if (node)
		return (node);
	*token_list = save;
	node = parser_cmd(token_list);
	if (node)
		return (node);
	*token_list = save;
	node = parser_redirect(token_list);
	if (node)
		return (node);
	return (NULL);
}

t_ast	*parser(t_token **token_list)
{
	t_ast	*syntax_tree;

	syntax_tree = init_tree(token_list);
	if ((syntax_tree && syntax_tree->type == ERROR) || !syntax_tree)
	{
		//exit_code = 2;
		//ast_free(syntax_tree);
		ft_putstr_fd("Syntax error\n", 2);
		return (NULL);
	}
	return (syntax_tree);
}
