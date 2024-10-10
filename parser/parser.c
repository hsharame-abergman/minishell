/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:50:50 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/10 16:17:38 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_ast	init_tree(t_token **token_list)
{

}

int	parser(t_token **token_list)
{
	t_ast	syntax_tree;

	syntax_tree = init_tree(token_list);
}
