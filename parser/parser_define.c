/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_define.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:37:29 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/15 21:19:00 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	is_cmd(char *value)
{
	if (ft_strcmp(value, "echo") == 0 || ft_strcmp(value, "cd") == 0
		|| ft_strcmp(value, "pwd") == 0 || ft_strcmp(value, "export") == 0
		|| ft_strcmp(value, "unset") == 0 || ft_strcmp(value, "env") == 0
		|| ft_strcmp(value, "exit") == 0)
		return (true);
	else
		return (false);
}

bool	is_flag(char *s)
{
	int	i;

	i = 2;
	if (s[0] == '-' && s[1] == 'n')
	{
		while (s[i] != '\0')
		{
			if (s[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

int	get_pars_type(char *value, int type)
{
	if (type == TOKEN_WORD)
	{
		if (is_cmd(value))
			return (CMD);
		else if (is_flag(value))
			return (FLAG);
		else
			return (ARGUMENT);
	}
	else if (type == REDIRECT_INPUT)
		return (REDIRECT_IN);
	else if (type == REDIRECT_OUTPUT)
		return (REDIRECT_OUT);
	else if (type == HEREDOC)
		return (NODE_HEREDOC);
	else if (type == APPEND_MODE)
		return (NODE_APPEND);
	else if (type == CHAR_DQUOTE)
		return (DQ_ARGUMENTS);
	else if (type == CHAR_DQUOTE)
		return (Q_ARGUMENT);
	return (ERROR);
}

bool	is_word_token(int type)
{
	if (type == TOKEN_WORD || type == CHAR_DQUOTE || type == CHAR_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_redirection_token(int type)
{
	if (type == REDIRECT_INPUT || type == REDIRECT_OUTPUT
		|| type == HEREDOC || type == APPEND_MODE)
		return (true);
	else
		return (false);
}
