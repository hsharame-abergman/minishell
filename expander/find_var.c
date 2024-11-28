/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:11:52 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/28 17:43:21 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*check_if_var(t_store *data, char *input)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup(input);
	while ((size_t)i < ft_strlen(res))
	{
		if (res[i] == '$' && (ft_isalpha(res[i + 1])
				|| res[i + 1] == '_'))
		{
			res = process_var(data, res, &i);
		}
		else if (res[i] == '$' && res[i + 1] == '?')
		{
			res = process_var_error(res, &i);
		}
		else if (res[i] == '$' && ft_isdigit(res[i + 1]))
		{
			res = process_digit_escape(res, &i);
		}
		else
			i++;
	}
	free(input);
	return (res);
}

void	variables_expansion(t_store *data, t_token *token, int *i)
{
	if (token->value[*i] == '$' && token->type != CHAR_QUOTE
		&& !check_escape(token->value, *i))
	{
		if (ft_isalpha(token->value[*i + 1])
			|| (token->value[*i + 1]) == '_')
			token->value = check_if_var(data, token->value);
		else if (token->value[*i + 1] == '?')
			token->value = check_if_var(data, token->value);
		else if (ft_isdigit(token->value[*i + 1]))
			token->value = check_if_var(data, token->value);
	}
}

void	expander(t_store *data, t_token **token_list)
{
	t_token	*token;
	int		i;

	token = *token_list;
	while (token)
	{
		if (is_word_token(token->type))
		{
			i = 0;
			while ((size_t)i < ft_strlen(token->value))
			{
				if (token->value[i + 1])
					variables_expansion(data, token, &i);
				else if (token->value[i] == '$' && token->is_adjacent)
					token->value = escape_dollar(token, &i);
				i++;
			}
		}
		token = token->next;
	}
}

bool	expander_heredoc(t_store *data, char *input)
{
	int	i;

	i = 0;
	(void)data;
	while (input[i])
	{
		if (input[i] == '$' && !check_escape(input, i)
			&& (ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
			return (true);
		i++;
	}
	return (false);
}
