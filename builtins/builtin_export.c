/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:44:23 by abergman          #+#    #+#             */
/*   Updated: 2024/10/25 11:51:33 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* ****************************************************** */
/* Adds the given variables to the enviroment variables.  */
/* Return 1 if one or more arguments were not added       */
/* and return 0 if all arguments were successfully added. */
/* ****************************************************** */

/* j'initialiser l'index pour iteration */
/* j'initialiser le statut de sortie du programme */

int	builtin_export(t_store *store, char **av)
{
	int		index;
	char	**temp;
	int		response;

	index = 1;
	response = EXIT_SUCCESS;
	
	if (!av[index]) 
	{
		return (builtin_env(store, NULL)); // если нет первого параметра то мы возвращаем 
	}
}
