/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:06:18 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/04 19:41:09 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c1;

	c1 = (unsigned char)c;
	if (c1 == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s)
	{
		if (*s == c1)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int	main(int argc, char *argv[])
{
	printf("%s\n", ft_strchr(argv[1], argv[2][0]));
	printf("%s\n", strchr(argv[1], argv[2][0]));
	return (argc);
}*/
