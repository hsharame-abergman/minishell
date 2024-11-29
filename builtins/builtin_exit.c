/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:49:11 by abergman          #+#    #+#             */
/*   Updated: 2024/11/29 01:55:15 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Checks whether the number LONG_MAX or LONG_MIN is exceeded. Sets boolean */
/* errors to true if the number is not in the range. false if it is not. */
static int	ft_check_out_of_range(int sign, unsigned long num, int *is_error)
{
	if ((sign == 1 && num > LONG_MAX)
		|| (sign == -1 && num > -(unsigned long)LONG_MIN))
		*is_error = 1;
	return (*is_error);
}

/* If exit is not called automatically, "exit" should not be issued. */
/* Returns true if exit should not be typed. False if exit was only called  */
/* and you should print "exit" message. */
static int	ft_is_silent_exit_mode(t_store *store)
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

/* Converts a string of numbers into a long integer. */
/* Returns a long integer. If an error occurs, sets boolean to true. */
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

/* Gets the exit code from arguments given in the built-in output file. */
/* Returns 0 if no arguments were presented. */
/* Returns 2 if the argument is not a number. */
/* Returns the digital exit code when successful. */
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

int	builtin_exit(t_store *store, char **av)
{
	int	exit_code;
	int	is_error;
	int	is_silent_mode;

	is_error = 0;
	is_silent_mode = ft_is_silent_exit_mode(store);
	if (!is_silent_mode && store->mode_usage == INTERACTIVE)
		ft_putendl_fd(B_EXIT, 2);
	if (!av || !av[1])
		exit_code = g_exit_code;
	else
	{
		exit_code = ft_get_exit_code(av[1], &is_error);
		if (is_error)
			exit_code = ft_error_handler(B_EXIT, av[1],
					"numeric argument required", 2);
		else if (av[2])
			return (ft_error_handler(B_EXIT, NULL, "too many arguments", 1));
	}
	ft_exit_program(store, exit_code);
	return (2);
}
