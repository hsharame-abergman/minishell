/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:27:04 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/23 18:10:34 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	cat << EOF
	> hello
	> $HOME
	> EOF
	hello
	/home/hsharame 
		! when writing to the temporary file, variables must already 
		be handled correctly
*/

char	*temp_file(int number)
{
	char	*res;
	char	*nombre;

	nombre = ft_itoa(number);
	res = ft_strjoin("TEMPORARY_FILE", nombre);
	free(nombre);
	return (res);
}

char	*check_if_var(char *input)
{
	char	**token;
	char	*env_value;
	int		i;

	i = 0;
	token = ft_split(input, ' ');
	if (!token)
		return (NULL);
	while (token[i])
	{
		token[i] = ft_strrchr(token[i], '$');
		if (token[i] != NULL)
		{
			env_value = getenv(token[i]);
			if (!env_value)
				token[i] = ft_strdup("");
			else
				token[i] = ft_strdup(env_value);
		}
		i++;
	}
	input = tab_to_str(token);
	free_tab(token);
	return (input);
}

bool	heredoc_succes(t_store *data, t_redirect *heredoc)
{
	int		fd;
	char	*input;

	(void)data;
	fd = open(heredoc->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		if (ft_strcmp(input, heredoc->delimiter) == 0)
			break ;
		if (ft_strrchr(input, '$') != NULL)
			input = check_if_var(input);
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	close(fd);
	return (true);
}

void	parse_heredoc(t_store *data, t_cmd **cmd, t_token **token)
{
	static int	number;
	t_token		*temp;

	temp = *token;
	create_redirect(*cmd);
	(*cmd)->redirect->delimiter = ft_strdup(temp->next->value);
	(*cmd)->redirect->infile = temp_file(number);
	if (heredoc_succes(data, (*cmd)->redirect))
		(*cmd)->redirect->fd_in = open((*cmd)->redirect->infile, O_RDONLY);
	else
		(*cmd)->redirect->fd_in = -1;
	number++;
	temp = temp->next->next;
	*token = temp;
}
