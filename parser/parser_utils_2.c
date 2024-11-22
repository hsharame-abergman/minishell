/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:03:14 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/22 14:29:10 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*fill_str(char *res, char **token)
{
	int	j;
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			res[len] = token[i][j];
			j++;
			len++;
		}
		if (token[i + 1])
			res[len++] = ' ';
		i++;
	}
	res[len] = '\0';
	return (res);
}

char	*tab_to_str(char **token)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (token[i])
	{
		len += strlen(token[i]);
		i++;
	}
	res = (char *)malloc(sizeof(char) * (len + i));
	if (!res)
		return (NULL);
	res = fill_str(res, token);
	return (res);
}

void	create_redirect(t_cmd *cmd)
{
	cmd->redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!cmd->redirect)
		return ;
	cmd->redirect->fd_in = -1;
	cmd->redirect->fd_out = -1;
	cmd->redirect->infile = NULL;
	cmd->redirect->outfile = NULL;
	cmd->redirect->delimiter = NULL;
}

void	check_if_exists(t_cmd *node)
{
	if ((node->value && node->path == NULL) || node->value[0] == '\0')
		cmd_error(node, 1);
	else
	{
		if (access(node->path, F_OK))
			cmd_error(node, 2);
		else if (access(node->path, X_OK))
			cmd_error(node, 3);
	}
}

void	cmd_error(t_cmd *node, int i)
{
	node->error = true;
	if (i == 1)
		printf("minishell: %s: command not found\n", node->value);
	else if (i == 2)
		printf("minishell: %s: No such file or directory\n", node->value);
	else if (i == 3)
		printf("minishell: %s: Permission denied\n", node->value);
}
