/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:50:50 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/26 17:23:29 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	The integer first is used to indicate that this is the first token that must
	be interpreted as a command. If first is equal to 0, the arguments are added
	to the already created t_cmd node, if first is 1, a new node is created and
	the previous node points to it. Redirects and pipes are managed separately.
*/

t_cmd	*init_tree(t_token **token_list, t_store *data)
{
	t_token	*save;
	t_cmd	*last_node;
	t_cmd	*current;
	int		first;

	save = *token_list;
	current = NULL;
	last_node = NULL;
	first = 1;
	while (save && save->type != END)
	{
		if (first == 1 && save->type != PIPE)
			current = handle_cmd(&save, &last_node, &first);
		else if (is_word_token(save->type))
			add_args(&save, current);
		else if (save->type == PIPE)
			handle_pipe(&save, &current, &first);
		else if (is_redirection_token(save->type))
			add_redirect(&save, &current, data);
		if (current->error == true)
			break ;
		last_node = current;
	}
	return (current);
}

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

void	add_args(t_token **save, t_cmd *cmd)
{
	int		count;
	int		i;
	t_token	*temp;

	temp = *save;
	i = 1;
	count = count_args(temp) + 2;
	cmd->args = (char **)malloc(sizeof(char *) * count);
	if (!cmd->args)
		return ;
	cmd->args[0] = ft_strdup(cmd->value);
	while (i < count - 1)
	{
		if ((*save)->is_adjacent == false)
			cmd->args[i] = ft_strdup((*save)->value);
		else
		{
			cmd->args[i] = ft_strjoin((*save)->value, (*save)->next->value);
			*save = (*save)->next;
		}
		*save = (*save)->next;
		i++;
	}
	cmd->args[count - 1] = NULL;
}

bool	parser(t_store *data, t_token *token_list)
{
	t_cmd	*syntax_tree;

	syntax_tree = init_tree(&token_list, data);
	if (!syntax_tree || syntax_tree->error == true)
	{
		if (syntax_tree)
			free_cmd(&syntax_tree);
		return (false);
	}
	while (syntax_tree && syntax_tree->left)
		syntax_tree = syntax_tree->left;
	data->pars = syntax_tree;
	return (true);
}
