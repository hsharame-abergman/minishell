/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:09:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/11 12:57:56 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	token_quotes(t_token **token_list, char *input, int *i, char quote)
{
	int		start;
	char	*value;

	start = ++(*i);
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
	return (0);
}

void	token_quotes_error(t_token **token_list, char *input, char quote)
{
	char	*value;
	int		start;

	start = 0;
	while (input[start] != quote)
		start++;
	value = ft_substr(input, start + 1, (size_t)(ft_strlen(input) - start - 3));
	value = ft_strjoin(value, "\n");
	if (quote == 39)
		add_token(token_list, value, CHAR_QUOTE);
	else if (quote == 34)
		add_token(token_list, value, CHAR_DQUOTE);
}

void	quotes(t_token **token_list, char *input, int *i)
{
	char	*extra_input;
	char	quote;

	quote = input[*i];
	if (token_quotes(token_list, input, i, quote) == -1)
	{
		ft_putstr_fd("> ", 1);
		extra_input = readline(NULL);
		while (extra_input)
		{
			input = ft_strjoin(input, extra_input);
			input = ft_strjoin(input, "\n");
			(*i) += ft_strlen(extra_input);
			if (ft_strchr(extra_input, quote) != NULL)
			{
				token_quotes_error(token_list, input, quote);
				free(extra_input);
				break ;
			}
			ft_putstr_fd("> ", 1);
			extra_input = readline(NULL);
		}
	}
}

void	token_word(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*token;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_isoperator(input[*i]))
		(*i)++;
	token = ft_substr(input, start, (size_t)(*i - start));
	if (token[0] == '-')
		add_token(token_list, token, OPTION);
	else
		add_token(token_list, token, TOKEN_WORD);
}
