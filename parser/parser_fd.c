/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:07 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/22 14:32:43 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
 	<		-	fd_in - stores the file descriptor
				infile - the name of the file to open
	open_input
	<<		-	fd_in - the file descriptor of the temporary file
				delimiter - the end marker provided by the user
	heredoc
	> >>	- 	fd_out - stores the file descriptor for writing
				outfile - the name of the file to open for writing
	open_file_trunc
	open_file_append
*/

bool	open_file_trunc(t_redirect *trunc, char *filename)
{
	trunc->outfile = ft_strdup(filename);
	trunc->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (trunc->fd_out == -1 && filename[0] != '\0')
	{
		ft_putstr_fd("Error\n", 2);
		return (false);
	}
	return (true);
}

bool	open_file_append(t_redirect *append, char *filename)
{
	append->outfile = ft_strdup(filename);
	append->fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (append->fd_out == -1 && filename[0] != '\0')
	{
		ft_putstr_fd("Error\n", 2);
		return (false);
	}
	return (true);
}

/*
	In case of input redirection, if the file does not already exist, 
	it does not create a new file and displays the error.
	bash: [filename]: No such file or directory
*/

bool	open_input(t_redirect *input, char *filename)
{
	input->infile = ft_strdup(filename);
	input->fd_in = open(filename, O_RDONLY);
	if (input->fd_in == -1 && filename[0] != '\0')
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (false);
	}
	return (true);
}
