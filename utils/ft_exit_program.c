/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:16 by abergman          #+#    #+#             */
/*   Updated: 2024/11/19 12:29:50 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Очистить программу minishell,
	закрыв все открытые fds и освободив всю выделенную память. */
void	ft_exit_program(t_store *store, int exit_code)
{
	if (store)
	{
		if (store->pars && store->pars->redirect)
			ft_close_fds(store->pars, 1);
		ft_free_store(store, 1);
	}
	rl_clear_history();
	exit(exit_code);
}
