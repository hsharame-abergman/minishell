/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:11:52 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/28 17:45:43 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


bool	check_escape(char *str, int i)
{
	if (str[i - 1] == '\"' && str[i + 1] == '\"')
		return (true);
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
			while (token->value[i])
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
