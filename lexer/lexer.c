/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:48:48 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/07 20:09:46 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **token_list, char value, int type)
{
	t_token	*new;
	t_token	*current;

	new = new_token(value, type);
	if (!token_list)
		*token_list = new;
	else
	{
		current = *token_list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int	get_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	if (token[0] == '<')
	{
		if (token[1] == '<')
			return (FIND_DELIMITER);
		return (REDIRECT_INPUT);
	}
	if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APPEND_MODE);
		return (REDIRECT_OUTPUT);
	}
}

void	init_tokens(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*value;

	start = *i;
	if (input[*i] == 34 || input[*i] == 39)
		token_quotes(token_list, input, &i);
	else if (ft_isoperator(input[*i]))
	{
		if (ft_isoperator(input[*i + 1]))
		{
			value = ft_substr(input, start, 2);
			(*i)++;
		}
		else
			value = ft_substr(input, start, 1);
		add_token(token_list, value, get_type(value));
		(*i)++;
	}
	else if (ft_isascii(input[*i]))
		token_word(token_list, input, &i);
	return ;
}

int	lexer(char *input)
{
	int		i;
	t_token	*token_list;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
			init_tokens(token_list, input, &i);
	}
	return (i);
}

