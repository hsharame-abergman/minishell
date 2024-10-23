/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:28:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/23 18:17:16 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// #TODO: Все коды ошибок которые не идут от сигналов не должны испольщовать глобальную переменную 

int	ft_set_env(t_store *store, char *key, char *value)
{
	int index;
	char *res;

	index = get_index_for_variable(store->envp, key);
	if (value == NULL)
		value = "";
	res = ft_strjoin("=", value);
	if (!res)
		return (0);
	if (index != -1 && (store->envp[index] != NULL))
	{
		ft_free_pointer(store->envp[index]);
		store->envp[index] = ft_strjoin(key, res);
	}
	ft_free_pointer(res);
	return(1);
} 
