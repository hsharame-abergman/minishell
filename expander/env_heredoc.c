/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:06:42 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/27 18:12:05 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Checks if in the value of each token there is an environment variable. 
	if so, replace it with its value, checking if there is no escape. otherwise,
	returns the initial value of input
*/

char	*get_env_value(t_store *data, char *input, int *i)
{
	char	*env_value;
	char	*res;
	int		length;
	int		start;

	start = *i;
	length = 0;
	while (input[*i + length] && (ft_isalnum(input[*i + length])
			|| input[*i + length] == '_'))
		length++;
	*i += length;
	res = ft_substr(input, start, length);
	env_value = ft_get_env_value(data->envp, res);
	free(res);
	if (!env_value)
		return (ft_strdup(""));
	else
		return (ft_strdup(env_value));
}

char	*replace_var(t_store *data, char *res, int *i)
{
	char	*env_value;
	char	*temp;
	char	*temp_2[2];
	char	*new_res;

	temp = ft_substr(res, 0, (*i)++);
	env_value = get_env_value(data, res, i);
	temp_2[0] = ft_substr(res, *i, ft_strlen(res) - *i);
	temp_2[1] = ft_strjoin(temp, env_value);
	new_res = ft_strjoin(temp_2[1], temp_2[0]);
	if (env_value[0] != '\0')
		*i += ft_strlen(env_value);
	else
		*i = 0;
	free(temp);
	free(env_value);
	free(temp_2[0]);
	free(temp_2[1]);
	return (new_res);
}

char	*check_if_var(t_store *data, char *input)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_strdup(input);
	while ((size_t)i < ft_strlen(res))
	{
		if (res[i] == '$' && (ft_isalnum(res[i + 1])
				|| res[i + 1] == '_'))
		{
			tmp = res;
			res = replace_var(data, res, &i);
			free(tmp);
		}
		else if (res[i] == '$' && res[i + 1] == '?')
			res = replace_var_error(res, &i);
		else
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
		if (input[i] == '$' && !check_escape(input, i) &&
			(ft_isalpha(input[i + 1]) || input[i + 1] =='_'))
			return (true);
		i++;
	}
	return (false);
}
