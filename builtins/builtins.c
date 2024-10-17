/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/17 19:03:51 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	*ft_builtins(t_store *store, char **av)
{
	if (is_builtins(av))
	{
		if (ft_strcmp(av[0], "pwd") == 0)
			builtin_pwd(store);
		else if (ft_strcmp(av[0], "cd") == 0)
			builtin_cd(store, av);
	}
	return (0);
}
