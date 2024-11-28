/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:10:17 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/28 15:10:52 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	count_args(t_token *save)
{
	int	i;

	i = 0;
	while (save && is_word_token(save->type))
	{
		if (save->is_adjacent == false)
			i++;
		save = save->next;
	}
	return (i);
}

/*
	Creates an argument table, where args[0] is always equal to the value
	(the command name) stored in the current node, the last element is
	always NULL, which allows to traverse the list of argument of a command
	from args[1] to args[count - 1].
*/

char	*join_args(char *stash, char *str, char *str2)
{
	char	*res;
	char	*tmp;

	if (stash == NULL)
		return (res = ft_strjoin(str, str2));
	else
	{
		tmp = ft_strjoin(stash, str);
		res = ft_strjoin(tmp, str2);
		free(tmp);
		free(stash);
		return (res);
	}
}

void	fill_args(t_token **save, t_cmd *cmd, int count)
{
	int		i;

	i = 1;
	while (i < count - 1)
	{
		if ((*save)->is_adjacent == false)
			cmd->args[i] = ft_strdup((*save)->value);
		while ((*save)->is_adjacent == true && (*save)->next->type != END)
		{
			if ((*save)->prev->is_adjacent == true)
				*save = (*save)->next;
			cmd->args[i] = join_args(cmd->args[i], (*save)->value,
					(*save)->next->value);
			*save = (*save)->next;
		}
		*save = (*save)->next;
		i++;
	}
}

void	add_args(t_token **save, t_cmd *cmd)
{
	int		count;
	int		i;
	t_token	*temp;

	temp = *save;
	i = 1;
	count = count_args(temp) + 2;
	cmd->args = (char **)ft_calloc(count, sizeof(char *));
	if (!cmd->args)
		return ;
	cmd->args[0] = ft_strdup(cmd->value);
	fill_args(save, cmd, count);
	cmd->args[count - 1] = NULL;
}
