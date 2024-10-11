/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:51:28 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/11 16:42:40 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_parser_type
{
	ERROR = -1
}	t_parser_type;

typedef struct s_ast
{
	char			*value;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_ast	*parser_cmd(t_token **token_list);
t_ast	*parser_pipe(t_token **token_list);
t_ast	*parser_redirect(t_token **token_list);
t_ast	*init_tree(t_token **token_list);
t_ast	*parser(t_token **token_list);
void	affiche_ast(t_ast *node);

#endif