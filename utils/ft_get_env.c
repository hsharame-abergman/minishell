/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:24:27 by abergman          #+#    #+#             */
/*   Updated: 2024/11/04 17:20:00 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Searches for the givenvariables inthe enviroment variables. */

/* Renvoie un pointeur vers la valeur de la variable dans l'environnement    */
/* correspondant à la chaîne donnée. Les noms de variables partiels sont non */
/* apportés: la chaîne donnée doit être un nom de variable complet.          */
/* Renvoie null si la chaîne ne peut être trouvée dans l'environnement.      */

char	*ft_get_env(char **envp, char *search)
{
	int			index;
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
