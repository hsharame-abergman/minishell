/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:46:28 by abergman          #+#    #+#             */
/*   Updated: 2024/10/28 19:34:21 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_get_env_index(char **envp, char *key)
{
    int i;
    char *res;

    i = 0;
    res = ft_strjoin(key, "=");
    if (!res)
        return (-1);
    while (envp[i])
    {
        if (ft_strncmp(res, envp[i], ft_strlen(res)) == 0)
        {
            ft_free_pointer(res);
            return (i);
        }
        i++;
    }
    ft_free_pointer(res);
    return (-1);
}

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
