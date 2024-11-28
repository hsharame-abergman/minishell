/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:08:21 by abergman          #+#    #+#             */
/*   Updated: 2024/11/28 15:54:45 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

bool	check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i + 1])
	{
		if (str[i] == '|' && str[i + 1] == ' ')
		{
			i++;
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '|')
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	check_several_operator(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 2)
	{
		while (str[i + 2] != '\0')
		{
			if (ft_isoperator(str[i]) && ft_isoperator(str[i + 1])
				&& ft_isoperator(str[i + 2]))
			{
				printf("minishell: syntax error near unexpected token");
				printf(" `%c%c'\n", str[i], str[i + 1]);
				return (false);
			}
			i++;
		}
	}
	return (true);
}

int	check_input(char *str)
{
	int	i;

	i = 0;
	if (!check_pipes(str) || !check_several_operator(str)
		|| !check_bracket(str))
		return (EXIT_GENERAL_ERROR);
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == ':' || str[i] == '!') && str[i + 1] == '\0')
		return (1);
	else if (str[i] == '>' || str[i] == '<' || str[i] == '&'
		|| (str[i] > 122 && str[i] < 126))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", str[i]);
		return (EXIT_GENERAL_ERROR);
	}
	else if (str[i] == '/' && str[i + 1] == '\0')
	{
		printf("minishell: /: Is a directory\n");
		return (EXIT_CMD_NOT_EXECUT);
	}
	else
		return (0);
}

int	ft_check_args(t_store *store, int ac, char **av, char **envp)
{
	if (envp == NULL || *envp == NULL)
		return (ft_putstr_fd("Error:\nNo environment found. Exiting.", 2), 0);
	if ((ac != 1 && ac != 3))
		return (ft_putstr_fd("Error:\nThe arguments is not valid.", 2), 0);
	if (ac == 3)
	{
		store->mode_usage = SINDLE_COMMAND;
		if (!av[1] || (av[1] && ft_strcmp(av[1], "-c") != 0))
			return (ft_putstr_fd("Error:\nFirst argument not found.", 2), 0);
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (ft_putstr_fd("Error:\nSecond argument not valid.", 2), 0);
	}
	else
		store->mode_usage = INTERACTIVE;
	return (1);
}

bool	void_input(t_store *data)
{
	int	i;

	i = 0;
	while (data->input[i] != '\0')
	{
		if (!ft_isspace(data->input[i]))
			return (false);
		i++;
	}
	return (true);
}
