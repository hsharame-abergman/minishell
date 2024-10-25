/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:48:48 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/25 16:55:50 by hsharame         ###   ########.fr       */
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

void	add_token(t_token **token_list, char *value, int type)
{
	t_token	*new;
	t_token	*current;

	new = new_token(value, type);
	if (!*token_list)
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
			return (HEREDOC);
		return (REDIRECT_INPUT);
	}
	if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APPEND_MODE);
		return (REDIRECT_OUTPUT);
	}
	return (-1);
}

void	init_tokens(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*value;

	start = *i;
	if (input[*i] == 34 || input[*i] == 39)
		quotes(token_list, input, i);
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
		token_word(token_list, input, i);
	return ;
}

bool	lexer(t_store *data)
{
	int		i;

	i = 0;
	while (data->input[i])
	{
		if (ft_isspace(data->input[i]))
			i++;
		else
		{
			init_tokens(&data->token, data->input, &i);
		}
	}	
	if (data->input[i] == '\0')
		add_token(&data->token, "\0", END);
	check_pipe(&data->token, data->input, &i);
	//affiche_tokens(data->token);
	expander(data, &data->token);
	parser(data, data->token);
	return (true);
}

