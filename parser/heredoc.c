/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:27:04 by hsharame          #+#    #+#             */
/*   Updated: 2024/10/25 18:28:12 by hsharame         ###   ########.fr       */
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
	char	*env_value;
	char	*temp;
	char	*temp_2;
	char	*res;
	char	*res_final;
	int		i;
	int		start;
	int		length;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && ft_isalpha(input[i + 1]))
		{
			temp = ft_substr(input, 0, i);
			start = i;
			length = 0;
			while (!ft_isspace(input[length]))
			{
				length++;
				i++;
			}
			temp_2 = ft_substr(input, i, ft_strlen(input) - i);
			res = ft_substr(input, start, length);
			env_value = getenv(res);
			if (!env_value)
				res = ft_strdup("");
			else
				res = ft_strdup(env_value);
			res_final = ft_strjoin(temp, res);
			res_final = ft_strjoin(res_final, temp_2);
			free(temp);
			free(res);
			free(temp_2);
		}
		i++;
	}
	free(input);
	return (res_final);
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
		if (ft_strchr(input, '$') != NULL)
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
