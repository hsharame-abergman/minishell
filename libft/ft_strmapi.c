/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:26:33 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/04 18:31:16 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	int			j;
	char		*result;

	i = ft_strlen(s);
	j = 0;
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result || !s || !f)
		return (NULL);
	while (s[j] != '\0')
	{
		result[j] = f(j, s[j]);
		j++;
	}
	result[j] = '\0';
	return (result);
}
