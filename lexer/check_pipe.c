/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:43:42 by hsharame          #+#    #+#             */
/*   Updated: 2024/12/04 16:47:02 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Check if input does not end with pipe.
	If so, ask to complete the input
*/

char	*input_pipe(t_token **token_list, char *input, int *i)
{
	char	*extra_input;
	char	*data_input;

	extra_input = readline("> ");
	extra_input = ft_strjoin(" ", extra_input);
	data_input = ft_strjoin(input, extra_input);
	free(extra_input);
	free(input);
	while (data_input[*i])
	{
		if (ft_isspace(data_input[*i]))
			(*i)++;
		else
			init_tokens(token_list, data_input, i);
	}
	if (data_input[*i] == '\0')
		add_token(token_list, "\0", END);
	return (data_input);
}

static void	ft_free_node(t_token *cmd)
{
	if (cmd->value)
		free(cmd->value);
	free(cmd);
	cmd = NULL;
}

bool	syntax_redir(t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->type == END)
		return (true);
	while (current->type != END)
	{
		if (is_redirection_token(current->type)
			&& is_redirection_token(current->next->type))
		{
			printf("minishell: syntax error near unexpected token");
			printf(" `%s'\n", current->next->value);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	syntax_pipe(t_token **token)
{
	t_token	*current;

	current = *token;
	if (current->type == END)
		return (true);
	while (current->next->type != END)
		current = current->next;
	if (current->type == PIPE)
	{
		if (current->prev
			&& is_redirection_token(current->prev->type))
		{
			error_syntax("syntax error near unexpected token `newline'\n",
				2, true);
			return (false);
		}
	}
	return (true);
}

char	*check_pipe(t_token **token_list, char *input, int *i)
{
	t_token	*current;

	current = *token_list;
	if (current->type == END)
		return (ft_strdup(input));
	while (current->next->type != END)
		current = current->next;
	if (current->type == PIPE)
	{
		ft_free_node(current->next);
		current->next = NULL;
		return (input_pipe(token_list, input, i));
	}
	return (ft_strdup(input));
}
