/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:43:42 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/27 16:47:18 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Check if input does not end with pipe.
	If so, ask to complete the input
*/

char	*input_pipe(t_token **token_list, char *input, int *i)
{
	char	*extra_input;
	char	*data_input;

	extra_input = readline("> ");
	extra_input = ft_strjoin(" ", extra_input);
	data_input = ft_strjoin(input, extra_input);
	free(extra_input);
	free(input);
	while (data_input[*i])
	{
		if (ft_isspace(data_input[*i]))
			(*i)++;
		else
			init_tokens(token_list, data_input, i);
	}
	if (data_input[*i] == '\0')
		add_token(token_list, "\0", END);
	return (data_input);
}

char	*check_pipe(t_token **token_list, char *input, int *i)
{
	t_token	*current;

	current = *token_list;
	if (current->type == END)
		return (ft_strdup(input));
	while (current->next->type != END)
		current = current->next;
	if (current->type == PIPE)
	{
		return (input_pipe(token_list, input, i));
	}
	return (ft_strdup(input));
}
