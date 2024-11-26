/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:11:52 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/26 16:47:05 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*replace_var_error(char *res, int *i)
{
	char	*env_value;
	char	*temp;
	char	*temp_2[2];
	char	*new_res;

	temp = ft_substr(res, 0, (*i)++);
	env_value = ft_itoa(g_exit_code);
	*i += ft_strlen(env_value);
	temp_2[0] = ft_substr(res, *i, ft_strlen(res) - *i);
	temp_2[1] = ft_strjoin(temp, env_value);
	new_res = ft_strjoin(temp_2[1], temp_2[0]);
	free(temp);
	free(env_value);
	free(temp_2[0]);
	free(temp_2[1]);
	return (new_res);
}

char	*var_error(char *value)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_strdup(value);
	while ((size_t)i < ft_strlen(res))
	{
		if (res[i] == '$' && res[i + 1] == '?')
		{
			tmp = res;
			res = replace_var_error(res, &i);
			free(tmp);
		}
		else
			i++;
	}
	free(value);
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
			token->value = var_error(token->value);
		else if (ft_isdigit(token->value[*i + 1]))
			token->value = escape_digit(token->value);
	}
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
				variables_expansion(data, token, &i);
				i++;
			}
		}
		token = token->next;
	}
}
