/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:27 by abergman          #+#    #+#             */
/*   Updated: 2024/11/12 11:03:36 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
   Поиск данной переменной в переменных среды.
   Возвращает указатель на значение переменной в окружении
   совпадает с данной строкой. Имена частичных переменных не
   поддерживается: указанная строка должна быть полным именем переменной.
   Возвращает NULL, если строка не может быть найдена в окружении.
*/
char	*ft_get_env_value(char **envp, char *search)
{
	int		index;
	char	*node;

	node = ft_strjoin(search, "=");
	if (!node)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(node, envp[index], ft_strlen(node)) == 0)
		{
			ft_free_pointer(node);
			return (ft_strchr(envp[index], '=') + 1);
		}
		index++;
	}
	ft_free_pointer(node);
	return (NULL);
}

/*
	Поиск данной переменной в переменных среды.

	Возвращает индекс переменной в окружении
	совпадает с данной строкой. Имена частичных переменных не
	поддерживается: указанная строка должна быть полным именем переменной.
	Возвращает -1, если строка не может быть найдена в окружении.
*/
int	ft_get_env_index(char **envp, char *key)
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
