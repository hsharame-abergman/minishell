/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/12/09 12:15:10 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Fill the char *path in the t_cmd node. If the command is a builtin or if it 
	is already passed with absolute path (if it contains /), we duplicate in
	this field the content of value. Otherwise, we search for the path.
*/

t_cmd	*parser_cmd(t_token *token, t_cmd *last)
{
	t_cmd	*current;

	current = create_node(token->value);
	if (last)
	{
		last->right = current;
		current->left = last;
	}
	if (is_builtin(current->value))
		current->path = ft_strdup(current->value);
	else
	{
		if (ft_strchr(current->value, '/') == NULL)
			current->path = define_path(current->value);
		else
			current->path = ft_strdup(current->value);
		check_if_exists(current);
	}
	return (current);
}

t_cmd	*parser_first_redir(t_token *token, t_cmd *last, t_store *data)
{
	t_cmd	*current;

	current = create_node(token->value);
	if (last)
	{
		last->right = current;
		current->left = last;
	}
	add_redirect(&token, &current, data);
	return (current);
}

void	join_cmd(t_token **save)
{
	char	*tmp;

	while (save && (*save)->is_adjacent)
	{
		tmp = (*save)->next->value;
		(*save)->next->value = ft_strjoin((*save)->value, tmp);
		ft_free_pointer(tmp);
		(*save) = (*save)->next;
	}
}

t_cmd	*handle_cmd(t_token **save, t_cmd **last, int *first, t_store *data)
{
	t_cmd	*current;

	current = NULL;
	if ((*save)->type == TOKEN_WORD && (*save)->value[0] == '\0')
		(*save) = (*save)->next;
	if ((*save)->type == END)
	{
		current = create_node("");
		current->error = true;
	}
	if (is_word_token((*save)->type))
	{
		if ((*save)->is_adjacent)
			join_cmd(save);
		current = parser_cmd(*save, *last);
		if (*save)
			*save = (*save)->next;
		*first = 0;
	}
	else if (is_redirection_token((*save)->type))
	{
		current = parser_first_redir(*save, *last, data);
		*save = (*save)->next->next;
	}
	return (current);
}

void	handle_pipe(t_token **save, t_cmd **current, int *first)
{
	if (*first == 1 && !current)
	{
		error_syntax("syntax error near unexpected token `|'\n", 2, true);
		(*current)->error = true;
		return ;
	}
	(*current)->pipe = true;
	*save = (*save)->next;
	*first = 1;
}
