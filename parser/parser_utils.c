/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:21 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/28 18:01:33 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*create_node(char *value)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	node->redirect = NULL;
	node->path = NULL;
	node->args = NULL;
	node->pipe = false;
	node->error = false;
	node->left = NULL;
	node->right = NULL;
	return (node);
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

bool	is_builtin(char *s)
{
	if (ft_strcmp(s, "cd") == 0)
		return (true);
	else if (ft_strcmp(s, "echo") == 0)
		return (true);
	else if (ft_strcmp(s, "env") == 0)
		return (true);
	else if (ft_strcmp(s, "exit") == 0)
		return (true);
	else if (ft_strcmp(s, "export") == 0)
		return (true);
	else if (ft_strcmp(s, "pwd") == 0)
		return (true);
	return (false);
}

void	affiche_ast(t_cmd *node)
{
	int	i;

	i = 1;
	if (!node)
		return ;
	printf("Commande : %s\n", node->value);
	printf("PATH : %s\n", node->path);
	if (node->args)
	{
		printf("Arguments : ");
		while (node->args[i])
		{
			printf("%d: %s ", i, node->args[i]);
				i++;
		}
		printf("\n");
	}
	if (node->pipe)
		printf("Pipe detected\n");
	affiche_ast(node->right);
}
