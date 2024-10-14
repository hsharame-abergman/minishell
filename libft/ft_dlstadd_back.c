/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 00:15:39 by abergman          #+#    #+#             */
/*   Updated: 2024/08/19 22:01:53 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **dist, t_dlist *new)
{
	t_dlist	*search_last;

	if (!(*dist))
	{
		*dist = new;
		return ;
	}
	if (!dist || !new)
		return ;
	if (*dist)
	{
		search_last = ft_dlstlast(*dist);
		search_last->next = new;
		new->prev = search_last;
	}
	else
		*dist = new;
}
