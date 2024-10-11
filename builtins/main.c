/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/11 18:56:39 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ◦ echo with option -n						*/
/* ◦ cd with only a relative or absolute path	*/
/* ◦ pwd with no options						*/
/* ◦ export with no options						*/
/* ◦ unset with no options						*/
/* ◦ env with no options or arguments			*/
/* ◦ exit with no options						*/

#include "builtins.h"

int	main(int ac, char **av, char **env)
{
	if (is_builtins(av))
	{
		if (ft_strcmp(av[0], "echo") == 0)
			builtin_echo(av);
		else if (ft_strcmp(av[0], "cd") == 0)
			builtin_cd(av);
	}
	return (0);
}
