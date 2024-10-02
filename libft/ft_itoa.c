/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:41:34 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/04 15:15:36 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

size_t	ft_size(int n)
{
	int		signe;
	size_t	size;

	size = 0;
	signe = 0;
	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		signe = 1;
	}
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size + signe);
}

char	*ft_put(int n, char *result, int size)
{
	int			i;
	long int	nb;

	i = size - 1;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		result[0] = '-';
	}
	result[size] = '\0';
	if (nb == 0)
	{
		result[i] = '0';
		return (result);
	}
	while (nb > 0)
	{
		result[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;

	size = ft_size(n);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result = ft_put(n, result, size);
	return (result);
}
/*
int main()
{
	char	*s;
	printf("%s\n", s = ft_itoa(-2147483648));
}*/
