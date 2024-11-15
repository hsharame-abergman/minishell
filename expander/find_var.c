/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:11:52 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/15 15:08:10 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	check_escape(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		return (false);
	}
	else
		return (false);
}

void	expander(t_store *data, t_token **token_list)
{
	t_token	*token;
	int		i;

	token = *token_list;
	(void)data;
	while (token)
	{
		if (is_word_token(token->type))
		{
			i = 0;
			while ((size_t)i < ft_strlen(token->value) && token->value[i + 1])
			{
				if (token->value[i] == '$' && ft_isalpha(token->value[i + 1])
					&& !check_escape(token->value, i)
					&& token->type != CHAR_QUOTE)
				{
					token->value = check_if_var(token->value);
				}
				i++;
			}
		}
		token = token->next;
	}
}
