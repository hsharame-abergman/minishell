/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:09:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/07 17:43:57 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_quotes(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*value;

	(*i)++;
	start = *i;
	while ((input[*i] != 34 && input[*i] != 39) && input[*i])
		(*i)++;
	value = ft_substr(input, start, i);
	if (input[*i] == 39)
		add_token(token_list, value, CHAR_DQUOTE);
	else if (input[*i] == 34)
		add_token(token_list, value, CHAR_QUOTE);
}

void	token_word(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*token;

	start = *i;
	while (!ft_isspace(input[*i]))
		(*i)++;
	token = ft_substr(input, start, i);
	add_token(token_list, token, TOKEN_WORD);
}
