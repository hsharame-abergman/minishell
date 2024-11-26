/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:39:35 by abergman          #+#    #+#             */
/*   Updated: 2024/11/26 14:48:20 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin2(char *dest, char *str)
{
	char	*temp;

	temp = NULL;
	if (!str)
		return (str);
	if (!dest)
		return (ft_strdup(str));
	temp = str;
	str = ft_strjoin(temp, str);
	ft_free_pointer(temp);
	return (str);
}

char	*ft_strjoin_freed(char *dest, char *str, t_free_arg index_free)
{
	char	*res;

	res = ft_strjoin(dest, str);
	if (index_free == FREE_DEST)
		free(dest);
	if (index_free == FREE_SRC)
		free(str);
	return (res);
}
