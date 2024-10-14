/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:50:50 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/14 15:43:02 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	*init_tree(t_token **token_list)
{
	t_token	*save;
	t_ast	*last_node;
	t_ast	*current;

	save = *token_list;
	current = NULL;
	last_node = NULL;
	while (save)
	{
		if (is_word_token(save->type))
			current = parser_cmd(save, last_node);
		else if (save->type == PIPE)
			current = parser_pipe(&save, last_node);
		else if (is_redirection_token(save->type))
			current = parser_redirect(&save, last_node);
		if (!current)
			return (NULL);
		last_node = current;
		save = save->next;
	}
	return (current);
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
