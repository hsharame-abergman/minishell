/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:42:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/18 18:10:06 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* 
The bash prompts are customised by setting the environment variable
Prompt String 1 (PS1) to the desired string in the ~/.bashrc file as follows,
    `\u`: The username of the current user
    `\h`: The hostname up to the first.
    `\H`: The full hostname
    `\w`: The current working directory
    `\W`: The basename of the current working directory
    `\$`: This code represents the prompt symbol, which is $ for a regular user
			and # for the root user

By default, the bash prompt includes the current username, hostname, and current
	working directory, followed by the `$` symbol for a regular user
	or the `#` symbol for the root user.
 */

char	*ft_hostname(void)
{
	char	buf[34];
	int		i;
	int		fd;
	char	*label;
	char	*res;

	fd = open("/etc/hostname", O_RDONLY);
	i = read(fd, buf, 20);
	buf[i] = '\0';
	close(fd);
	if (i > 0)
	{
		i = 0;
		while (buf[i] && buf[i] != '.')
			i++;
	}
	res = ft_substr(buf, 0, i);
	label = ft_strjoin(res, ":");
	free(res);
	return (label);
}

char	*ft_create_label_for_readline(char **envp, t_store *store)
{
	char	*label;
	char	*hostname;
	char	*res;

	label = ft_strjoin(ft_get_env_value(envp, "USER"), "@");
	hostname = ft_hostname();
	res = ft_strjoin(label, hostname);
	res = ft_strjoin(res, ft_get_env_value(store->envp, "PWD"));
	res = ft_strjoin(res, "$ ");
	free(label);
	free(hostname);
	return (res);
}

void	ascii_welcome(void)
{
	printf("      _____\n  ___|    _|__  ____  ____   _  ____  ______ ");
	printf(" __   _  ______  ____    ____\n |    \\  /  | ||    ||    \\ | ||");
	printf("    ||   ___||  |_| ||   ___||    |  |    |\n |     \\/   | || ");
	printf("   ||     \\| ||    | `-.`-. |   _  ||   ___||    |_ |    |_\n");
	printf(" |__/\\__/|__|_||____||__/\\____||____||______||__| |_||");
	printf("______||______||______|\n     |_____|\n\n");
	printf("Copyright (c) by abergman & hsharame\n\n");
}
