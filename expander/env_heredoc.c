/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:06:42 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/19 16:29:19 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Checks if in the value of each token there is an environment variable. 
	if so, replace it with its value, checking if there is no escape. otherwise,
	returns the initial value of input
*/

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
		i = 0;
		while (input[i] && input[i] != '$')
			i++;
		if (input[i] && ft_isalpha(input[i]))
		{
			temp = ft_substr(res, 0, i - 1);
			env_value = get_env_value(res, &i);
			temp_2 = ft_substr(res, i, ft_strlen(res) - i);
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

bool	expander_heredoc(t_store *data, char *input)
{
	int	i;

	i = 0;
	(void)data;
	while (input[i])
	{
		if (input[i] == '$' && ft_isalpha(input[i + 1])
			&& !check_escape(input, i))
			return (true);
		i++;
	}
	return (false);
}
