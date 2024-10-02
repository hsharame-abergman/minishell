/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:04:57 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/04 19:29:49 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "libft.h"
/*
void    *ft_memset(void *s, int c, size_t n)
{
        char    *ptr;
        size_t  i;

        i = 0;
        ptr = (char *)s;
        while (i < n)
        {
                ptr[i] = c;
                i++;
        }
        return (s);
}*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = (void *)malloc(sizeof(void) * (nmemb * size));
	if (!result)
		return (NULL);
	ft_bzero(result, size * nmemb);
	return (result);
}
/*
int main()
{
	int	*arr;
	int	i = 0;

	arr = (int *)ft_calloc(5, sizeof(int));
	while (i < 5)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
	       i++;
	}
}*/	
