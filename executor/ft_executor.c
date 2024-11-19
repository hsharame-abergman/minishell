/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:42:08 by abergman          #+#    #+#             */
/*   Updated: 2024/11/19 15:47:09 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	Ждет, пока дети закончат после очистки фдс и списка команд.
	Возвращает статус выхода из программы как и bash:
		"Статус возврата (см. Exit Status) простой команды
			- это её статус выхода,
			как это предусмотрено функцией POSIX 1003.1 waitpid, или 128+n,
			если команда была закончена сигналом n."

	Если в конвейере имеется несколько команд:
		"Статус вывода трубопровода
			- это статус вывода последней команды в трубопроводе"
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
	Создаёт дочерний процесс для каждой исполняемой команды,
		за исключением встроенной команды,
		которая не будет запущена и будет выполняться в основном процессе (в данном случае не создано дочерних).
	Возвращает true,
		когда процесс был создан для каждой команды или когда встроенный файл был выполнен самостоятельно.
	Возвращает false, если была ошибка в ответвлении.
*/
int	ft_create_children_process(t_store *store)
{
	t_cmd	*command;

	command = store->pars;
	while (command && store->pid != 0)
	{
		store->pid = fork();
		if (store->pid == -1)
			return (ft_error_handler("fork", NULL, "", 1));
		else if (store->pid)
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
		if (store->pars->redirect && !ft_check_io(store->pars->redirect))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!ft_create_pipes(store))
		return (EXIT_FAILURE);
	return (EXIT_CMD_NOT_FOUND);
}

/*
	Выполняет указанные команды, создавая дочерние процессы и ожидая
	их завершения. Возвращает код выхода последнего из числа подлежащих
	удалению. Или код выхода 1 в случае провала процесса создания подлежащего удалению.
*/
int	ft_executor(t_store *store)
{
	int exit_code;	

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
