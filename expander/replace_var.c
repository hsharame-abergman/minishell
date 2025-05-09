/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:06:42 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/28 13:43:12 by hsharame         ###   ########.fr       */
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
