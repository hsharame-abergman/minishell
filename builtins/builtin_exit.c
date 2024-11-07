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

static int ft_check_out_of_range(int sign, unsigned long num, int *is_error)
{
	if ((sign == 1 && num > LONG_MAX)
		|| (sign == -1 && num > -(unsigned long)LONG_MIN))
		*is_error = 1;
	return (*is_error);
}

static int	ft_is_silent_mode(t_store *store)
{
	t_cmd	*command;

	command = store->pars;
	if (!command)
		return (0);
	if (command->left != NULL)
		return (1);
	if (command->right != NULL)
		return (1);
	return (0);
}

static int	ft_atol_err(char *ascii, int *is_error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (ascii[i] && ft_isspace(ascii[i]))
		i++;
	if (ascii[i] == '+')
		i++;
	else if (ascii[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (ascii[i] && ft_isdigit(ascii[i]))
	{
		num = (num * 10) + (ascii[i] - '0');
		if (ft_check_out_of_range(neg, num, is_error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	ft_get_exit_code(char *cmd, int *is_error)
{
	unsigned long long	i;

	if (!cmd)
		return (g_exit_code);
	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		*is_error = 1;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	if (!ft_isdigit(cmd[i]))
		*is_error = 1;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]) && !ft_isspace(cmd[i]))
			*is_error = 1;
		i++;
	}
	i = ft_atol_err(cmd, is_error);
	return (i % 256);
}

void	ft_exit_program(t_store *store, int exit_code)
{
	if (store)
	{
		if (store->pars && store->pars->redirect)
			ft_close_fds(store->pars, 1);
		ft_free_store(store, 1);
	}
	exit(exit_code);
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
	ft_exit_program(store, exit_code);
	return (2);
}
