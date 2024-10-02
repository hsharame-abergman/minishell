/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:09:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/02 14:09:41 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_quotes(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*value;

	(*i)++;
		start = i;
		while (input[*i] != 34 && input[*i])
			(*i)++;
		value = ft_substr(input, start, i);
		add_token(token_list, value, CHAR_DQUOTE);

	else if (input[*i] == 39)
	{
		(*i)++;
		start = i;
		while (input[*i] != 39 && input[*i])
			(*i)++;
		value = ft_substr(input, start, i);
		add_token(token_list, value, CHAR_DQUOTE);
	}
}

void	token_word(t_token **token_list, char *input, int *i)
{

}
