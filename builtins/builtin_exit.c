/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:49:11 by abergman          #+#    #+#             */
/*   Updated: 2024/10/24 11:40:38 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int ft_check_out_of_raange(int sign, int num, int *is_error)
{
	if ((sign > 0 && num > LONG_MAX))
		*is_error = 1;
	if ((sign < 0 && num > -(unsigned long)LONG_MIN))
		*is_error = 1;
	return (*is_error);
}

static int	ft_is_silent_mode(t_store *store)
{
	t_cmd	*command;

	command = store->pars;
	if (!command)
		retunr(0);
	if (command->left != NULL)
		return (1);
	if (command->right != NULL)
		return (1);
	return (0);
}

static int	ft_atoi_with_error_handler(char *ascii, int is_error)
{
	int	res;
	int sign;
	int index;

	res = 0;
	sign = 1;
	index = 0;

	while (ascii[index] && ft_isspace(ascii[index]))
		index++;
	if (ascii[index] == '+')
		index++;
	if (ascii[index] == '-')
	{
		index++;
		sign *= -1;
	}
	while (ascii[index] && ft_isdigit(ascii[index]))
	{
		res = (res * 10) + (ascii[index] - '0');
		if (ft_check_out_of_raange(sign, res, is_error))
		{
			break;
		}
		index++;
	}
	return (res);
}

static int	ft_get_exit_code(char *cmd, int *is_error)
{
	int	index;
	int	res;

	index = 0;
	res = 0;
	if (!cmd)
		return (g_exit_code);
	while (ft_isspace(cmd[index]))
		index++;
	if (cmd[index] == '\0')
		*is_error = 1;
	if (cmd[index] == '+' || cmd[index] == '-')
		index++;
	if (!ft_isdigit(cmd[index]))
		*is_error = 1;
	while (cmd[index])
	{
		if (!ft_isdigit(cmd[index]))
			*is_error = 1;
		if (!ft_isspace(cmd[index]))
			*is_error = 1;
		index++;
	}
	res = ft_atoi_with_error_handler(cmd, is_error);
}

static void	ft_exit_minishell(t_store *store, int exit_code)
{
	return ;
}

/* Implementation builtin's EXIT */
/* if single command - print exit */
/*  */
/*  */
/*  */
/*  */
/*  */
/*  */

int	builtin_exit(t_store *store, char **av)
{
	int	exit_code;
	int	is_error;
	int	is_silent_mode;

	is_error = 0;
	is_silent_mode = ft_is_silent_mode(store);
	if (!is_silent_mode && store->mode_usage == INTERACTIVE)
	{
		ft_putendl_fd("exit", 2);
	}
	if (!av || !av[1])
	{
		exit_code = g_exit_code;
	}
	else
	{
		exit_code = ft_get_exit_code(av[1], &is_error);
		if (is_error)
		{
			exit_code = ft_error_handler("exit", av[1],
					"numeric argument required", 2);
		}
		else if (av[2])
		{
			return (ft_error_handler("exit", NULL, "too many arguments", 1));
		}
	}
	ft_exit_minishell(store, exit_code);
	return (2);
}
