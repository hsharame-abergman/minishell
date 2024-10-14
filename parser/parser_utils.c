/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:21 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/14 17:47:24 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	*create_node(char *value, int type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	get_pars_type(char *value, int type)
{
	if (type == TOKEN_WORD)
	{
		if (is_cmd(value))
			return (CMD);
		else if (is_flag(value))
			return (FLAG);
		else
			return (ARGUMENT);
	}
	else if (type == REDIRECT_INPUT)
		return (REDIRECT_IN);
	else if (type == REDIRECT_OUTPUT)
		return (REDIRECT_OUT);
	else if (type == HEREDOC)
		return (NODE_HEREDOC);
	else if (type == APPEND_MODE)
		return (NODE_APPEND);
	else if (type == CHAR_DQUOTE)
		return (DQ_ARGUMENTS);
	else if (type == CHAR_DQUOTE)
		return (Q_ARGUMENT);
}

bool	is_word_token(int type)
{
	if (type == TOKEN_WORD || type == CHAR_DQUOTE || type == CHAR_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_redirection_token(int type)
{
	if (type == REDIRECT_INPUT || type == REDIRECT_OUTPUT
		|| type == HEREDOC || type == APPEND_MODE)
		return (true);
	else
		return (false);
}

void	affiche_ast(t_ast *node)
{
	if (node == NULL)
		return ;
	else if (node->type == NODE_PIPE)
		printf("%s | %s\n", node->left->value, node->right->value);
	else if (node->type == REDIRECT_IN)
		printf("%s < %s\n", node->left->value, node->right->value);
	else if (node->type == REDIRECT_OUT)
		printf("%s > %s\n", node->left->value, node->right->value);
	else if (node->type == NODE_HEREDOC)
		printf("%s << %s\n", node->left->value, node->right->value);
	else if (node->type == NODE_APPEND)
		printf("%s >> %s\n", node->left->value, node->right->value);
	else
		printf("left:%s %s right:%s\n", node->left->value, node->value,
			node->right->value);
	affiche_ast(node->right);
}
