/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:11:13 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/04 20:18:18 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	c1;

	i = ft_strlen(s);
	c1 = (unsigned char)c;
	if (c1 == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		if (s[i] == c1)
			return ((char *)&s[i]);
		i--;
	}
	if (s[0] == c1)
		return ((char *)&s[i]);
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	printf("%s\n", ft_strrchr("hello world", 'l'));
	printf("%s\n", strrchr("hello world", 'l'));
}*/
