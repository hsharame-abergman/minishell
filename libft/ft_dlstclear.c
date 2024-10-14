/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:58:42 by abergman          #+#    #+#             */
/*   Updated: 2024/08/25 14:13:16 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **dlst, void (*del)(void *))
{
	void	*prev;

	if (!del || !dlst || !(*dlst))
		return ;
	while (*dlst)
	{
		del((*dlst)->content);
		prev = *dlst;
		*dlst = (*dlst)->next;
		del(prev);
	}
	dlst = NULL;
}
