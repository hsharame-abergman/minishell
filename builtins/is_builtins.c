/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:42:48 by abergman          #+#    #+#             */
/*   Updated: 2024/10/14 17:13:35 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* ◦ echo with option -n						*/
/* ◦ cd with only a relative or absolute path	*/
/* ◦ pwd with no options						*/
/* ◦ export with no options						*/
/* ◦ unset with no options						*/
/* ◦ env with no options or arguments			*/
/* ◦ exit with no options						*/

int	is_builtins(char **av)
{
	(void)av;
	if (av[0] == "cd")
		builtin_cd();
	else if (av[0] == "echo")
		builtin_echo();
	else if (av[0] == "env")
		builtin_env();
	else if (av[0] == "exit")
		builtin_exit();
	else if (av[0] == "export")
		builtins_export();
	else if (av[0] == "pwd")
		builtins_pwd();
	return (1);
}
