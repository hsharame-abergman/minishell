/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:27:45 by abergman          #+#    #+#             */
/*   Updated: 2024/08/25 14:14:51 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstlast(t_dlist *dlist)
{
	if (!dlist)
		return (NULL);
	while (dlist->next)
	{
		dlist = dlist->next;
	}
	return (dlist);
}
