/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:04:57 by abergman          #+#    #+#             */
/*   Updated: 2024/10/11 20:42:14 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_cd(char *av)
{
	if (av[1] = NULL)
		printf(stderr, "cd: expected argument\n");
	else
	{
		if (chdir(av[1]) != 0)
			perror("cd");
	}
	return (1);
}
