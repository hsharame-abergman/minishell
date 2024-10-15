/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:21 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/15 22:22:14 by hsharame         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	affiche_ast(t_ast *node)
{
	int	i;

	i = 1;
	while (node != NULL)
	{
		if (node->left)
		{
			printf("%d. left:%s %s right:%s\n", i, node->left->value, node->value,
				node->right->value);
			printf("%d. left:%d %d right:%d\n", i, node->left->type, node->type,
				node->right->type);
		}
		else if (node->right)
		{
			printf("%d. %s right:%s\n", i, node->value, node->right->value);
			printf("%d. %d right:%d\n", i, node->type, node->right->type);
		}
		else
		{
			printf("%d. %s\n", i, node->value);
			printf("%d. %d\n", i, node->type);
		}
		i++;
	}
}
