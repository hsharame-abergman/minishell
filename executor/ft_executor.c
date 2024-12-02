/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsharame <hsharame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:42:08 by abergman          #+#    #+#             */
/*   Updated: 2024/12/02 17:08:29 by hsharame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Wait for the children to finish after cleaning the FDS and the command list.
	Returns the program exit status like bash:
		"Return status (see Exit Status) simple command
			- is its status as an output,
			as provided by the POSIX 1003.1 waitpid function, or 128+n,
			if the command was terminated by n."

	If there are more than one command in the pipeline:
		"Pipeline exit status is the state of the last command in the pipeline"
*/
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
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WEXITSTATUS(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (save_status);
}

/*
	Creates a child process for each command,
		except for the built-in command,
		that will not be run and will be executed in the main process
		(no child is created in this case).
	Returns true when the process was created for each command 
	or when the embedded file was run by itself.
	Returns false if there was an error in the branch.
*/
int	ft_create_children_process(t_store *store)
{
	t_cmd	*command;

	command = store->pars;
	while (command && store->pid != 0)
	{
		store->pid = fork();
		if (store->pid == -1)
			return (ft_error_handler("fork", NULL, strerror(errno),
					EXIT_FAILURE));
		else if (store->pid == 0)
		{
			ft_execute_command(store, command);
		}
		command = command->right;
	}
	return (ft_get_children(store));
}

/* Prepares command list execution. */
/* Create pipes and check files.	*/
int	ft_preporation_for_execution(t_store *store)
{
	if (!store || !store->pars)
		return (EXIT_SUCCESS);
	if (!store->pars->value)
	{
		if (store->pars->redirect && !ft_check_io(store->pars->redirect))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!ft_create_pipes(store))
		return (EXIT_FAILURE);
	return (EXIT_CMD_NOT_FOUND);
}

/*
	Executes the specified commands, creating child processes and waiting for
	The end of each sequence. Returns the code of the last number to be
	to delete. Or exit code 1 if the process of creating a deletion has failed.
*/
int	ft_executor(t_store *store)
{
	int	exit_code;

	exit_code = ft_preporation_for_execution(store);
	if (exit_code != EXIT_CMD_NOT_FOUND)
		return (exit_code);
	if (!store->pars->pipe && !store->pars->left
		&& ft_check_io(store->pars->redirect))
	{
		ft_redirect_io(store->pars->redirect);
		exit_code = ft_execute_builtin(store, store->pars);
		ft_restore_io(store->pars->redirect);
	}
	if (exit_code != EXIT_CMD_NOT_FOUND)
		return (exit_code);
	return (ft_create_children_process(store));
}
