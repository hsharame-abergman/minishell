/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:42:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/12/07 22:36:06 by abergman         ###   ########.fr       */
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

	fd = open("/goinfre/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("42"));
	i = read(fd, buf, 20);
	buf[i] = '\0';
	close(fd);
	if (i > 0)
	{
		i = 0;
		while (buf[i] && buf[i] != '.' && buf[i] != '\n')
			i++;
	}
	res = ft_substr(buf, 0, i);
	label = ft_strjoin(res, ":");
	free(res);
	return (label);
}

char	*ft_set_pwd(t_store *store)
{
	char	*pwd;
	char	*home;
	char	*res[2];

	pwd = ft_get_env_value(store->envp, "PWD");
	if (!pwd)
		pwd = "";
	res[0] = ft_strdup(pwd);
	home = ft_get_env_value(store->envp, "HOME");
	if (!home)
		home = "";
	if ((ft_strcmp(pwd, home)) >= 0)
	{
		res[1] = ft_substr(pwd, ft_strlen(home), ft_strlen(pwd));
		if (ft_strlen(res[1]) >= 0)
		{
			free(res[0]);
			res[0] = ft_strjoin("~", res[1]);
			if (res[1])
				free(res[1]);
			return (res[0]);
		}
		free(res[1]);
	}
	return (res[0]);
}

char	*ft_create_label_for_readline(t_store *store)
{
	char	*label;
	char	*hostname;
	char	*pwd;
	char	*res[2];
	char	*user;

	user = ft_get_env_value(store->envp, "USER");
	if (!user)
		user = ft_strdup("");
	label = ft_strjoin(user, "@");
	hostname = ft_hostname();
	res[0] = ft_strjoin(label, hostname);
	pwd = ft_set_pwd(store);
	res[1] = ft_strjoin_free(res[0], pwd, FREE_DEST);
	res[0] = ft_strjoin_free(res[1], "$ ", FREE_DEST);
	free(label);
	free(hostname);
	free(pwd);
	return (res[0]);
}

void	ascii_welcome(void)
{
	printf("      _____\n  ___|    _|__  ____  ____   _  ____  ______ ");
	printf(" __   _  ______  ____    ____\n |    \\  /  | ||    ||    \\ | ||");
	printf("    ||   ___||  |_| ||   ___||    |  |    |\n |     \\/   | || ");
	printf("   ||     \\| ||    | `-.`-. |   _  ||   ___||    |_ |    |_\n");
	printf(" |__/\\__/|__|_||____||__/\\____||____||______||__| |_||");
	printf("______||______||______|\n     |_____|");
	printf("Copyright (c) by abergman & hsharame\n\n");
}
