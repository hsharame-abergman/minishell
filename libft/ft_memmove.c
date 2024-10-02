/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:38:08 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/03 20:31:07 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}
/*
int	main()
{
	char	src[30] = "J'adore l'ecole 42";
	char    src1[30] = "J'adore l'ecole 42";
	char    src2[30] = "J'adore l'ecole 42";
	char	*dest;
	char	*dest1;
	char	*dest2;
	printf("%s  -   %s\n", dest = ft_memmove(src+5, src, 13), src);
	printf("%s  -   %s\n", dest1 = memmove(src1+5, src1, 13), src1);
	printf("%s  -   %s\n", dest2 = memcpy(src2+5, src2, 13), src2);
}*/
