/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:50:50 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/21 18:52:19 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
		i++;
		save = save->next;
	}
	return (i);
}

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
		cmd->args[i] = ft_strdup((*save)->value);
		*save = (*save)->next;
		i++;
	}
	cmd->args[count - 1] = NULL;
}

void	parser(t_store *data, t_token *token_list)
{
	t_cmd	*syntax_tree;

	syntax_tree = init_tree(&token_list, data);
	while (syntax_tree->left)
		syntax_tree = syntax_tree->left;
	affiche_ast(syntax_tree);
	data->pars = syntax_tree;
}


/*	if (!syntax_tree && !check_cmd(syntax_tree) || !check_grammar(syntax_tree))
	{
		ft_putstr_fd("Syntax error\n", 2);
		return (NULL);
	}
	*/