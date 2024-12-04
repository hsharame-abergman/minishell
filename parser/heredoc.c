/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:27:04 by hsharame          #+#    #+#             */
/*   Updated: 2024/12/04 15:51:28 by abergman         ###   ########.fr       */
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

void	ft_heredoc_routine(t_store *store, t_redirect *heredoc, int fd)
{
	char	*input;

	signal(SIGINT, heredoc_signal_handler);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("minishell: warning: here-document delimited ");
			printf("by end-of-file (wanted `%s')\n", heredoc->delimiter);
			exit(0);
		}
		if (ft_strcmp(input, heredoc->delimiter) == 0)
		{
			free(input);
			break ;
		}
		if (expander_heredoc(store, input))
			input = check_if_var(store, input);
		ft_putendl_fd(input, fd);
		free(input);
	}
	exit(0);
}

/*
	Heredoc creates a temporary file. The string or character passed
	after the heredoc sign << is called delimiter and is stored in the
	t_redirect structure stored in the t_cmd. Using the ft_putendl_fd function,
	to which we pass the created temporary file fd, we store the additional
	input with the return line until we find the delimiter.
*/

bool	heredoc_succes(t_store *store, t_redirect *heredoc)
{
	int	fd;
	int	pid;
	int	status;

	reset_redirect(heredoc, true);
	fd = open(heredoc->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (false);
	pid = fork();
	if (pid < 0)
	{
		close(fd);
		return (false);
	}
	if (pid == 0)
		ft_heredoc_routine(store, heredoc, fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	close(fd);
	if (WIFSIGNALED(status))
		ft_error_handler("signal", NULL, "Process terminated by signal", 2);
	if (!WIFEXITED(status))
		ft_error_handler("signal", NULL, "Process terminated abnormally", 2);
	return (true);
}

/*
	This function is used to manage the heredoc and create a temporary
	file that will have a unique name thanks to static int, which is
	implemented each time this function is called.
*/

bool	parse_heredoc(t_store *data, t_cmd **cmd, t_token **token)
{
	static int	number;
	t_token		*temp;

	temp = *token;
	if (temp->next->value[0] == '\0')
		return (false);
	create_redirect(*cmd);
	(*cmd)->redirect->delimiter = ft_strdup(temp->next->value);
	(*cmd)->redirect->infile = temp_file(number);
	if (heredoc_succes(data, (*cmd)->redirect))
	{
		(*cmd)->redirect->fd_in = open((*cmd)->redirect->infile, O_RDONLY);
		if ((*cmd)->redirect->fd_in == -1)
			return (false);
	}
	else
		(*cmd)->redirect->fd_in = -1;
	number++;
	temp = temp->next->next;
	*token = temp;
	return (true);
}
