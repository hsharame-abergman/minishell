/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:28:40 by abergman          #+#    #+#             */
/*   Updated: 2024/10/28 12:40:24 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int ft_env_var_count(char **envp)
{
	int index;

	index = 0;
	while (envp[index])
		index++;
	return (index);
}

int ft_get_index_variable(char **env, const char *variable)
{
	int index;
	char *res;

	res = ft_strjoin(variable, "=");
	if (!res)
		return (-1);
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(res, env[index], ft_strlen(res)) == 0)
		{
			ft_free_pointer(res);
			return (index);
		}
	}
	ft_free_pointer(res);
	return (-1);
}

static char **ft_realloc_env_vars(t_store *store, int count)
{
	char **n_env;
	int index;

	n_env = ft_calloc(count + 1, sizeof(n_env));
	if (!n_env)
		return (NULL);
	index = 0;
	while (store->envp[index] && index < count)
	{
		n_env[index] = ft_strdup(store->envp[index]);
		ft_free_pointer(store->envp[index]);
		index++;
	}
	free(store->envp);
	return (n_env);
}

// #TODO: Все коды ошибок которые не идут от сигналов не должны испольщовать глобальную переменную 

int	ft_set_env(t_store *store, char *key, char *value)
{
	int index;
	char *res;

	index = ft_get_index_variable(store->envp, key);
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
	else
	{
		index = ft_env_var_count(store->envp);
		store->envp = ft_realloc_env_vars(store, index + 1);
		if (!store->envp)
		{
			return (0);
		}
		store->envp[index] = ft_strjoin(key, res);
	}
	ft_free_pointer(res);
	return(1);
} 
