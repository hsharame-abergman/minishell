/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:42:39 by hsharame          #+#    #+#             */
/*   Updated: 2024/11/14 17:54:34 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	close (fd);
	if (i > 0)
	{
		i = 0;
		while (buf[i] && buf[i] != '.')
			i++;
	}
	res = ft_substr(buf, 0, i);
	label = ft_strjoin(res, ": ");
	free(res);
	return (label);
}

char	*ft_create_label_for_readline(char **envp)
{
	char	*label;
	char	*hostname;
	char	*res;

	label = ft_get_env_value(envp, "USER");
	label = ft_strjoin(label, "@");
	hostname = ft_hostname();
	res = ft_strjoin(label, hostname);
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
