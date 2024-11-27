/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:41:53 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/27 17:15:34 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] != NULL)
			ft_free_pointer(tab[i]);
		i++;
	}
	ft_free_pointer(tab);
}

void	free_token(t_token **token_list)
{
	t_token	*temp;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	temp = *token_list;
	while (temp && temp->prev != NULL)
		temp = temp->prev;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
	*token_list = NULL;
}

void	free_redirect(t_redirect *node)
{
	if (node->outfile != NULL)
		free(node->outfile);
	if (node->delimiter && node->infile)
		unlink(node->infile);
	if (node->infile != NULL)
		free(node->infile);
	if (node->delimiter != NULL)
		free(node->delimiter);
	free(node);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = *cmd;
	while (temp && temp->left != NULL)
		temp = temp->left;
	while (temp != NULL)
	{
		next = temp->right;
		free(temp->value);
		free(temp->path);
		if (temp->args != NULL)
			free_tab(temp->args);
		if (temp->redirect != NULL)
			free_redirect(temp->redirect);
		free(temp);
		temp = next;
	}
	*cmd = NULL;
}
