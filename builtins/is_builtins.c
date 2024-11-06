/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:42:48 by abergman          #+#    #+#             */
/*   Updated: 2024/11/06 17:51:49 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* ◦ echo with option -n						*/
/* ◦ cd with only a relative or absolute path	*/
/* ◦ pwd with no options						*/
/* ◦ export with no options						*/
/* ◦ unset with no options						*/
/* ◦ env with no options or arguments			*/
/* ◦ exit with no options						*/

int	is_builtins(t_store *store, char **av)
{
	(void)av;
	if (ft_strcmp(av[0], "cd"))
		builtin_cd(store, av);
	else if (ft_strcmp(av[0], "echo"))
		builtin_echo(av);
	else if (ft_strcmp(av[0], "env"))
		builtin_env(store, av);
	else if (ft_strcmp(av[0], "exit"))
		builtin_exit(store, av);
	else if (ft_strcmp(av[0], "export"))
		builtin_export(store, av);
	else if (ft_strcmp(av[0], "pwd"))
		builtin_pwd(store);
	return (1);
}
