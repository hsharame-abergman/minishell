/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:58:10 by abergman          #+#    #+#             */
/*   Updated: 2024/11/13 20:36:52 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Create a set of pipes for each piped command in list of commands. */

int	ft_create_pipes(t_store *store)
{
	int		*fd;
	t_cmd	*response;

	response = store->pars;
	while (response)
	{
		if (response->pipe || (response->left && response->left->pipe))
		{
			fd = malloc(sizeof(fd) * 2);
			if (!fd || pipe(fd) != 0)
				return (ft_free_store(store, 0), 0);
			response->fd_pipe = fd;
		}
		response = response->right;
	}
	return (1);
}
