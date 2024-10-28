/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:06:42 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/28 14:30:59 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_env_value(char *input, int *i)
{
	char	*env_value;
	char	*res;
	int		length;
	int		start;

	start = *i;
	length = 0;
	while (input[*i + length] && ft_isalnum(input[*i + length]))
		length++;
	*i += length;
	res = ft_substr(input, start, length);
	env_value = getenv(res);
	free(res);
	if (!env_value)
		return (ft_strdup(""));
	else
		return (ft_strdup(env_value));
}

char	*check_if_var(char *input)
{
	char	*env_value;
	char	*temp;
	char	*temp_2;
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup(input);
	while (input[i])
	{
		if (input[i] == '$' && ft_isalpha(input[i + 1]))
		{
			temp = ft_substr(input, 0, i++);
			env_value = get_env_value(input, &i);
			temp_2 = ft_substr(input, i, ft_strlen(input) - i);
			res = ft_strjoin(temp, env_value);
			res = ft_strjoin(res, temp_2);
			free(temp);
			free(env_value);
			free(temp_2);
		}
		i++;
	}
	free(input);
	return (res);
}

bool	expander_heredoc(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && ft_isalpha(input[i + 1])
			&& !check_escape(input, i))
			return (true);
		i++;
	}
	return (false);
}
