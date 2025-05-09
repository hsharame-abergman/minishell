/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/25 16:01:58 by hsharame         ###   ########.fr       */
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

bool	init_lexer(t_store *data)
{
	int		input_check;

	input_check = check_input(data->input);
	if (input_check != 0)
	{
		g_exit_code = input_check;
		return (false);
	}
	if (data->token)
		reset_tokens(&data->token);
	return (true);
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
