/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:52:15 by hsharame          #+#    #+#             */
/*   Updated: 2024/06/05 13:57:54 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "libft.h"
/*
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
}*/

int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

char	**ft_result(char const *s, char c)
{
	int		count;
	char	**result;

	count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!s || !result)
		return (NULL);
	result[count] = NULL;
	return (result);
}
/*
void	ft_free(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
}*/

int	put_split(char const *s, char c, char **res)
{
	int	count;
	int	i;
	int	start;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			res[count] = (char *)malloc(sizeof(char) * (i - start + 1));
			if (!res[count])
				return (0);
			ft_memcpy(res[count], s + start, i - start);
			res[count++][i - start] = '\0';
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = ft_result(s, c);
	if (result == NULL)
		return (NULL);
	if (!put_split(s, c, result))
		return (NULL);
	return (result);
}
/*
int main()
{
	char **result = ft_split("      split       this for   me  !       ", ' ');
	printf ("%s\n", result[1]);
}*/
