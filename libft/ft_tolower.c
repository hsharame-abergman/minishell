/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:02:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/05/24 19:13:48 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c += 32);
	else
		return (c);
}
/*
#include <stdio.h>
int main()
{
	printf("%c - Z, %c - A, %c - 8",  ft_tolower('Z'), 
			ft_tolower('A'), ft_tolower('8'));
}*/
