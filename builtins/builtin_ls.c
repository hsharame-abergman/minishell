/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:44:56 by abergman          #+#    #+#             */
/*   Updated: 2024/11/16 19:42:46 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ft_destroy_ls(int *count, DIR *pointer_dir)
{
	if (--(*count) % 5 != 0)
		printf("\n");
	*count = 1;
	return (closedir(pointer_dir), 0);
}

int	builtin_ls(t_store *store)
{
	static struct s_format	format = {1};
	struct dirent			*p_dirent;
	DIR						*pointer_dir;
	char					*path;

	path = ft_get_env_value(store->envp, "PWD");
	pointer_dir = opendir(path);
	if (pointer_dir == NULL)
		return (printf("Cannot open directory '%s'\n", path), 1);
	while (1)
	{
		p_dirent = readdir(pointer_dir);
		if (p_dirent == NULL)
			return (ft_destroy_ls(&format.counter, pointer_dir));
		if ((ft_strcmp(p_dirent->d_name, ".") == 0
				|| ft_strcmp(p_dirent->d_name, "..") == 0
				|| (*p_dirent->d_name) == '.'))
			continue ;
		printf("%s\t", p_dirent->d_name);
		if (ft_strlen(p_dirent->d_name) <= 7)
			printf("\t");
		if (format.counter % 5 == 0)
			printf("\n");
		format.counter++;
	}
}

