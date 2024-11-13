/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/13 20:26:11 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	reset_tokens(t_token **token)
{
	t_token	*current;
	t_token	*prev;

	current = *token;
	while (current)
	{
		prev = current->prev;
		free(current->value);
		free(current);
		current = prev;
	}
	*token = NULL;
}

bool	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	else
		return (false);
}

bool	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	affiche_tokens(t_token *token_list)
{
	while (token_list != NULL)
	{
		printf("value %s, type %d\n", token_list->value, token_list->type);
		token_list = token_list->next;
	}
}

/*
	Check if input does not end with pipe.
	If so, ask to complete the input
*/

void	check_pipe(t_token **token_list, char *input, int *i)
{
	t_token	*current;
	char	*extra_input;

	current = *token_list;
	while (current->next->type != END)
		current = current->next;
	if (current->type == PIPE)
	{
		extra_input = readline("> ");
		input = ft_strjoin(input, extra_input);
		free(extra_input);
		while (input[*i])
		{
			if (ft_isspace(input[*i]))
				(*i)++;
			else
				init_tokens(token_list, input, i);
		}
		free(input);
	}
}
