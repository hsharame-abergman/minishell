/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/07 20:09:37 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	else
		return (false);
}

bool	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}
