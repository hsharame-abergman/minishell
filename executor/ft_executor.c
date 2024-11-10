/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:42:08 by abergman          #+#    #+#             */
/*   Updated: 2024/11/10 16:33:45 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_check_redirect(t_redirect *redirect)
{
	if (!redirect || (!redirect->outfile))
		return (1);
	if ((redirect->infile && redirect->fd_in == -1) || (redirect->outfile
			&& redirect->fd_out))
		return (0);
	return (1);
}

int	ft_get_children(t_store *store)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	ft_close_fds(store->pars, 0);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == store->pid)
			save_status = status;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WEXITSTATUS(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (save_status);
}

/* Create a set of pipes for each piped command in list of commands. */
int	ft_create_pipes(t_store *store)
{
	int		*fd;
	t_cmd	*response;

	response = store->pars;
	while (response)
	{
		if (response->pipe || (response->left && response->left->pipe))
		{
			if (!(fd = malloc(sizeof(fd) * 2)) || pipe(fd) != 0)
				return (ft_free_store(store, 0), 0);
			response->fd_pipe = fd;
		}
		response = response->right;
	}
	return (EXIT_SUCCESS);
}

int	ft_create_children_process(t_store *store)
{
	t_cmd	*command;

	command = store->pars;
	while (store->pid != 0 && command)
	{
		store->pid = fork();
		if (store->pid == -1)
			return (ft_error_handler("fork", NULL, "", 1));
		else if (store->pid == 0)
		{
			ft_execute_command(store, command);
		}
		command = command->right;
	}
	return (ft_get_children(store));
}
/* ******************************** */
/* Prepares command list execution. */
/* Create pipes and check files.	*/

int	ft_preporation_for_execution(t_store *store)
{
	if (!store || !store->pars)
		return (EXIT_SUCCESS);
	if (!store->pars->value)
	{
		if (store->pars->redirect && !ft_check_redirect(store->pars->redirect))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!ft_create_pipes(store))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

/* ************************************************************************ */
/* Executes given commands by creating child processes and waiting			*/
/* for them to finish. Returns the exit code of the last child to finish.	*/
/* Returns exit code 1 if creating a child process fails. 					*/

int	ft_redirect_io(t_redirect *redirect)
{
	int	response;

	response = 1;
	if (!redirect)
		return (0);
	redirect->stdin_backup = dup(STDIN_FILENO);
	if (redirect->stdin_backup == -1)
		response = ft_error_handler("dup", "stdin backup", strerror(errno), 1);
	if (redirect->stdout_backup == -1)
		response = ft_error_handler("dup", "stdout backup", strerror(errno), 1);
	if (redirect->fd_in != -1)
		if (dup2(redirect->fd_in, STDIN_FILENO) == -1)
			response = ft_error_handler("dup2", redirect->infile,
					strerror(errno), 1);
	if (redirect->fd_out != -1)
		if (dup2(redirect->fd_out, STDOUT_FILENO) == -1)
			response = ft_error_handler("dup2", redirect->outfile,
					strerror(errno), 1);
	return (response);
}

int	ft_check_io(t_redirect *redirect)
{
	if (!redirect || (!redirect->infile && !redirect->outfile))
		return (1);
	if ((redirect->infile && redirect->fd_in == -1) || (redirect->outfile
			&& redirect->fd_out == -1))
		return (0);
	return (1);
}

int	ft_restore_io(t_redirect *redirect)
{
	int	response;

	response = 1;
	if (!redirect)
		return (response);
	if (redirect->stdin_backup != -1)
	{
		if (dup2(redirect->stdin_backup, STDIN_FILENO) == -1)
			response = 0;
		close(redirect->stdin_backup);
		redirect->stdout_backup = -1;
	}
	if (redirect->stdout_backup != -1)
	{
		if (dup2(redirect->stdout_backup, STDOUT_FILENO) == -1)
			response = 0;
		close(redirect->stdout_backup);
		redirect->stdout_backup = -1;
	}
	return (response);
}

int	ft_executor(t_store *store)
{
	int	response;

	response = ft_preporation_for_execution(store);
	if (response != CMD_NOT_FOUND)
		return (response);
	if (!store->pars->pipe && !store->pars->left
		&& ft_check_redirect(store->pars->redirect))
	{
		ft_redirect_io(store->pars->redirect);
		response = ft_builtins(store, store->pars);
		ft_restore_io(store->pars->redirect);
	}
	if (response != CMD_NOT_FOUND)
		return (response);
	return (ft_create_children_process(store));
}
