/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:03:28 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/05 12:49:20 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 Returns the substring of the given string at the given start position 
 with the given length (or smaller if the length of the original string 
 is less than start + length, or length is bigger than MAXSTRINGLEN). 
#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h>

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
        char            *d;
        const char      *s;

        d = (char *)dest;
        s = (const char *)src;
        while (n)
        {
                *d = *s;
                d++;
                s++;
                n--;
        }
        return (dest);
}
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	length;

	length = ft_strlen(s);
	if (start >= length || length == 0)
	{
		result = (char *)malloc(sizeof(char) * 1);
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	if (len > length - start)
		len = length - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result = ft_memcpy(result, s + start, len);
	result[len] = '\0';
	return (result);
}
/*
int	main()
{
	printf("%s\n", ft_substr("hello, world bonjour", 7, 6));
}*/
