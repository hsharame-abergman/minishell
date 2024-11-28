/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:38:43 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/28 13:52:03 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*process_var(t_store *data, char *res, int *i)
{
	char	*tmp;

	tmp = res;
	res = replace_var(data, res, i);
	free(tmp);
	return (res);
}

char	*process_var_error(char *res, int *i)
{
	char	*tmp;

	tmp = res;
	res = replace_var_error(res, i);
	free(tmp);
	return (res);
}

char	*process_digit_escape(char *res, int *i)
{
	char	*tmp;
	char	*temp;
	char	*temp_2;

	tmp = res;
	temp = ft_substr(res, 0, *i);
	*i += 2;
	temp_2 = ft_substr(res, *i, ft_strlen(res) - *i);
	res = ft_strjoin(temp, temp_2);
	free(tmp);
	free(temp);
	free(temp_2);
	return (res);
}
