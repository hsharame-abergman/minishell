/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/17 13:30:01 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	else
		return (false);
}

bool	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	affiche_tokens(t_token *token_list)
{
	while (token_list != NULL)
	{
		printf("value %s, type %d\n", token_list->value, token_list->type);
		token_list = token_list->next;
	}
}

void	check_pipe(t_token **token_list, char *input, int *i)
{
	t_token	*current;
	char	*extra_input;

	current = *token_list;
	while (current->next != NULL)
		current = current->next;
	if (current->type == PIPE)
	{
		ft_putstr_fd("> ", 1);
		extra_input = readline(NULL);
		input = ft_strjoin(input, extra_input);
		while (input[*i])
		{
			if (ft_isspace(input[*i]))
				(*i)++;
			else
				init_tokens(token_list, input, i);
		}
	}
}
