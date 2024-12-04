/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:55:22 by hsharame          #+#    #+#             */
/*   Updated: 2024/12/04 15:21:35 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	SIGINT (Ctrl-C): Interrupts the current command and displays a new prompt
	on a new line.
	SIGQUIT (Ctrl-\): Ignored, so it should do nothing.
	Ctrl-D (exits the shell): Cannot be caught as a signal, but is detected by
	checking if readline returns NULL.
*/

void	signal_ctrl_c(int sign)
{
	(void)sign;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = EXIT_CMD_INTERRUPTED;
}

void	ft_set_signals_interactive(void)
{
	struct sigaction	signal;

	signals_ignore();
	sigemptyset(&signal.sa_mask);
	signal.sa_handler = &signal_ctrl_c;
	signal.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal, NULL);
}

void	signals_ignore(void)
{
	struct sigaction	signal;

	sigemptyset(&signal.sa_mask);
	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &signal, NULL);
}

void	heredoc_signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_code = 130;
	exit(130);
}
