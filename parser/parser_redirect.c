/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/23 18:09:35 by hsharame         ###   ########.fr       */
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
		return ;
	}
	if ((*save)->type == REDIRECT_INPUT)
		parse_input(current, save);
	else if ((*save)->type == REDIRECT_OUTPUT)
		parse_trunc(current, save);
	else if ((*save)->type == HEREDOC)
		parse_heredoc(data, current, save);
	else if ((*save)->type == APPEND_MODE)
		parse_append(current, save);
}

void	parse_append(t_cmd **cmd, t_token **token)
{
	t_token	*temp;

	temp = *token;
	create_redirect(*cmd);
	open_file_append((*cmd)->redirect, temp->next->value);
	temp = temp->next->next;
	*token = temp;
}

void	parse_input(t_cmd **cmd, t_token **token)
{
	t_token	*temp;

	temp = *token;
	create_redirect(*cmd);
	open_input((*cmd)->redirect, temp->next->value);
	temp = temp->next->next;
	*token = temp;
}

void	parse_trunc(t_cmd **cmd, t_token **token)
{
	t_token	*temp;

	temp = *token;
	create_redirect(*cmd);
	open_file_trunc((*cmd)->redirect, temp->next->value);
	temp = temp->next->next;
	*token = temp;
}
