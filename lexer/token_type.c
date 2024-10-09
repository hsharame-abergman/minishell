/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:09:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/09 18:08:30 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	token_quotes(t_token **token_list, char *input, int *i)
{
	int		start;
	char	*value;
	char	quote;
	int		j;

	j = *i;
	printf("%s\n %d i a ce momemnt\n", input, j);
	while (input[j] != 34 && input[j] != 39)
		j--;
	printf("%c\n", input[j]);
	quote = input[j];
	(*i)++;
	start = j;
	printf("%d\n", start);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	printf("%d\n", *i);
	if (input[*i] != quote)
		return (-1);
	value = ft_substr(input, start, (size_t)(*i - start + 1));
	if (input[*i] == 39)
		add_token(token_list, value, CHAR_QUOTE);
	else if (input[*i] == 34)
		add_token(token_list, value, CHAR_DQUOTE);
	(*i)++;
	return (0);
}

void	quotes(t_token **token_list, char *input, int *i)
{
	char	*extra_input;

	if (token_quotes(token_list, input, i) == -1)
	{
		ft_putstr_fd("> ", 1);
		extra_input = readline(NULL);
		while (extra_input)
		{
			input = ft_strjoin(input, extra_input);
			(*i) += ft_strlen(extra_input);
			free(extra_input);
			if (token_quotes(token_list, input, i) == 0)
				break ;
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
	while (input[*i] && !ft_isspace(input[*i]))
		(*i)++;
	token = ft_substr(input, start, (size_t)(*i - start));
	if (token[0] == '-')
		add_token(token_list, token, OPTION);
	else
		add_token(token_list, token, TOKEN_WORD);
}
