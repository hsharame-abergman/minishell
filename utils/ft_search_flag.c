/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:04:28 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:54:21 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Checks if an argument is an option flag -n.  */
/* If the value is -n or -nnnn on returns 1 also */
/* If the value is - or n or -nnnm on returns 0, error   */
int	ft_search_flag(char *str, char flag)
{
	int	index;
	int	is_flag;

	is_flag = 0;
	index = 0;
	if (str[index] != '-')
		return (is_flag);
	index++;
	while (str[index] && str[index] == flag)
		index++;
	if (str[index] == '\0')
		is_flag = 1;
	return (is_flag);
}
