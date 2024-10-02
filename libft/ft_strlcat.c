/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:23:59 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/04 16:42:17 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <bsd/string.h>
/*
size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while (s[i] != '\0')
                i++;
        return (i);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size == 0 || size <= i)
		return (size + j);
	j = 0;
	while (i + j < (size - 1) && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (ft_strlen(src) + i);
}
/*
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>
#include <stddef.h>

int	main()
{
	char dst1[20] = "Hello, ";
	char src1[] = "world";
	char dst[20] = "Hello, ";      
        char src[] = "world";
	printf("%ld la taille et la chaine est %s\n", ft_strlcat(dst1, src1, -1), dst1);
	printf("%ld la taille et la chaine est %s\n", strlcat(dst, src, -1), dst);
}*/
