/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:39:35 by abergman          #+#    #+#             */
/*   Updated: 2024/11/11 15:28:54 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin2(char *dest, char *str)
{
	char	*temp;

	temp = NULL;
	if (!str || !dest)
		ft_free_pointer(temp);
	if (!str)
		return (str);
	if (!dest)
		return (ft_strdup(str));
	temp = str;
	str = ft_strjoin(temp, str);
	ft_free_pointer(temp);
	return (str);
}
