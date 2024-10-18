/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/18 17:58:42 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_builtins(t_store *store, char **av)
{
	if (is_builtins(store, av))
	{
		if (ft_strcmp(av[0], "pwd") == 0)
			builtin_pwd(store);
		else if (ft_strcmp(av[0], "cd") == 0)
			builtin_cd(store, av);
	}
	return (0);
}
