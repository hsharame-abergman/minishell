/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:46:32 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/21 18:53:39 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	add_redirect(t_token **save, t_cmd **current, t_store *data)
{
	(void)data;
	if ((*save)->next->type == END)
	{
		error_syntax("syntax error near unexpected token `newline'\n", 2);
		(*current)->error = true;
		return ;
	}
	//(*current)->redirect = 
}
