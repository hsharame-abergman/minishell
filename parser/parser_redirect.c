/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/22 14:21:10 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	<< HEREDOC
	< REDIRECT_INPUT
	>> APPEND_MODE
	> REDIRECT_OUTPUT
*/

void	add_redirect(t_token **save, t_cmd **current, t_store *data)
{
	if ((*save)->next->type == END)
	{
		error_syntax("syntax error near unexpected token `newline'\n", 2);
		(*current)->error = true;
	}
	if ((*save)->type == REDIRECT_INPUT)
	{
		if (!parse_input(current, save))
			(*current)->error = true;
	}
	else if ((*save)->type == REDIRECT_OUTPUT)
	{
		if (!parse_trunc(current, save))
			(*current)->error = true;
	}
	else if ((*save)->type == HEREDOC)
	{
		if (!parse_heredoc(data, current, save))
			(*current)->error = true;
	}
	else if ((*save)->type == APPEND_MODE)
	{
		if (!parse_append(current, save))
			(*current)->error = true;
	}
}

bool	parse_append(t_cmd **cmd, t_token **token)
{
	t_token	*temp;
	bool	res;

	temp = *token;
	create_redirect(*cmd);
	res = open_file_append((*cmd)->redirect, temp->next->value);
	temp = temp->next->next;
	*token = temp;
	return (res);
}

bool	parse_input(t_cmd **cmd, t_token **token)
{
	t_token	*temp;
	bool	res;

	temp = *token;
	create_redirect(*cmd);
	res = open_input((*cmd)->redirect, temp->next->value);
	temp = temp->next->next;
	*token = temp;
	return (res);
}

bool	parse_trunc(t_cmd **cmd, t_token **token)
{
	t_token	*temp;
	bool	res;

	temp = *token;
	create_redirect(*cmd);
	res = open_file_trunc((*cmd)->redirect, temp->next->value);
	temp = temp->next->next;
	*token = temp;
	return (res);
}
