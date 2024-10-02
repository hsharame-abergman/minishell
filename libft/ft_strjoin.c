/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:35:26 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/05 12:31:11 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
/*
size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while (s[i] != '\0')
                i++;
        return (i);
}*/

char	*ft_concat(char const *s1, char const *s2, char *res, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i + j < n)
	{
		while (s1[i] != '\0')
		{
			res[i] = s1[i];
			i++;
		}
		res[i + j] = s2[j];
		j++;
	}
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!result)
		return (NULL);
	result = ft_concat(s1, s2, result, (i + j + 1));
	return (result);
}
/*
int	main()
{
	char	*dest;
	printf("%s\n", dest = ft_strjoin("hello ", "world"));
}*/
