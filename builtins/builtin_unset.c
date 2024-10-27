/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:46:28 by abergman          #+#    #+#             */
/*   Updated: 2024/10/27 21:21:29 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	builtin_unset(t_store *store, char **av)
{
    int i;
    int j;
    int response;

    response = EXIT_SUCCESS;
    while(av[i])
    {
        if (!ft_env_is_valid(av[i]) || ft_strchar(av[i], '=') != NULL)
        {
            ft_error_handler("unset", av[i], "not a valid identifier", 1);
            response = EXIT_FAILURE;
        }
        else
        {
            i = ft_get_env_index(store->envp, av[i]);
            if (i != -1)
            {
                ft_remove_env(store, i);
            }
        }
        i++;
    }
    return (response);
}
