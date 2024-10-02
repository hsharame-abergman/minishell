/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:09:24 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/02 11:09:26 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define TOKEN_WORD 1
# define OPTION 2
# define PIPE 3
# define REDIRECT_INPUT 4
# define REDIRECT_OUTPUT 5
# define FIND_DELIMITER 6
# define APPEND_MODE 7
# define ENVIRONMENT 8
# define CHAR_QUOTE 9
# define CHAR_DQUOTE 10

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

#endif
