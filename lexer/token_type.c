/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:09:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/25 13:28:42 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	is_adjacent(t_token **token_list)
{
	t_token	*current;

	current = *token_list;
	if (current)
	{
		while (current && current->next)
			current = current->next;
		current->is_adjacent = true;
	}
}

int	token_quotes(t_token **token_list, char *input, int *i, char quote)
{
	int		start;
	char	*value;

	(*i)++;
	start = *i;
	if (input[*i - 2] && !ft_isspace(input[*i - 2]))
		is_adjacent(token_list);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (-1);
	value = ft_substr(input, start, (size_t)(*i - start));
	if (quote == 39)
		add_token(token_list, value, CHAR_QUOTE);
	else if (quote == 34)
		add_token(token_list, value, CHAR_DQUOTE);
	(*i)++;
	if (input[*i] && !ft_isspace(input[*i]))
		is_adjacent(token_list);
	return (0);
}

void	token_quotes_error(t_token **token_list, char *input, char quote)
{
	char	*value;
	int		start;
	int		end;

	start = 0;
	while (input[start] != quote)
		start++;
	end = ft_strlen(input);
	while (input[end] != quote)
		end--;
	value = ft_substr(input, start + 1, end - start - 1);
	if (quote == 39)
		add_token(token_list, value, CHAR_QUOTE);
	else if (quote == 34)
		add_token(token_list, value, CHAR_DQUOTE);
}

bool	quotes(t_token **token_list, char *input, int *i)
{
	char	quote;

	quote = input[*i];
	if (token_quotes(token_list, input, i, quote) == -1)
	{
		error_syntax("error: unclosed quotes\n", 2, true);
		return (false);
	}
	return (true);
}

void	token_word(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*token;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_isoperator(input[*i])
		&& input[*i] != 34 && input[*i] != 39)
		(*i)++;
	token = ft_substr(input, start, (size_t)(*i - start));
	add_token(token_list, token, TOKEN_WORD);
	free(token);
}
