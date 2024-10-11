/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:21 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/11 16:36:40 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	affiche_ast(t_ast *node)
{
	if (node == NULL)
		return ;
	else if (node->type == PIPE)
		printf("%s | %s\n", node->left->value, node->right->value);
	else if (node->type == REDIRECT_INPUT)
		printf("%s < %s\n", node->left->value, node->right->value);
	else if (node->type == REDIRECT_OUTPUT)
		printf("%s > %s\n", node->left->value, node->right->value);
	else if (node->type == HEREDOC)
		printf("%s << %s\n", node->left->value, node->right->value);
	else if (node->type == APPEND_MODE)
		printf("%s >> %s\n", node->left->value, node->right->value);
	else
		printf("%s\n", node->value);
}
