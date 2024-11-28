/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:56:03 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/28 18:04:27 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	check_escape(char *str, int i)
{		
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		return (false);
	}
	else
		return (false);
}

char	*escape_dollar(t_token *token, int *i)
{
	char	*temp;
	char	*temp_2;
	char	*res;

	temp = ft_substr(token->value, 0, *i);
	*i += 2;
	temp_2 = ft_substr(token->value, *i,
			ft_strlen(token->value) - *i);
	res = ft_strjoin(temp, temp_2);
	free(temp);
	free(temp_2);
	free(token->value);
	return (res);
}

char	*escape_digit(char *str)
{
	char	*res;
	char	*temp;
	char	*temp_2;
	int		i;

	i = 0;
	res = ft_strdup(str);
	while ((size_t)i < ft_strlen(res))
	{
		if (res[i] == '$' && ft_isdigit(res[i + 1]))
		{
			temp = ft_substr(res, 0, i);
			i += 2;
			temp_2 = ft_substr(res, i, ft_strlen(res) - i);
			res = ft_strjoin(temp, temp_2);
			free(temp);
			free(temp_2);
		}
		else
			i++;
	}
	free(str);
	return (res);
}
