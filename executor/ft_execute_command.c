#include "../header/minishell.h"

/*
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*	Returns CMD_NOT_FOUND if a path to the executable bin file cannot be
*	found. Returns 1 in case of failure to run existing, executable
*	file.
*/
int ft_execute_sys_bin(t_store *store, t_cmd *cmd)
{
  if (!cmd->value && cmd->value == "\0")
    {
      return (127);
    }

}

/*
*	Child process tries to execute the given command by setting
*	its input/output fds and searching for an executable.
*	Searching for executable in this order:
*		1. Execute builtin command
*		2. Execute system binaries for command.
*		3. Execute given command name directly (local bin)
*	If it cannot find a matching builtin or executable,
*	prints an error message.
*	Child exits with it's executed program's exit code, or 1 if
*	it could not find one.
*/
int    ft_execute_command(t_store *store, t_cmd *cmd)
{
      int    response;
      int  error;

      if (!cmd || cmd->value)
      {
            error = ft_error_handler("child", NULL, "parsing error: command not found", EXIT_FAILURE);
            ft_exit_program(store, error);
      }
      if (!ft_check_io(cmd->redirect))
        ft_exit_program(store, EXIT_FAILURE);
      ft_set_pipe_fds(store->pars, cmd);
      ft_redirect_io(cmd->redirect);
      ft_close_fds(store->pars, 0);
      if (ft_strchr(cmd->value, '/') == NULL)
        {
           response = ft_execute_command(store, cmd);
           if (response != 127)
             ft_exit_program(store, response);
           response = ft_execute_sys_bin(store, cmd);
           if (response != 127)
             ft_exit_program(store, response);
        }
        response = ft_execute_local_bin(store, cmd);
        ft_exit_program(store, response);
      return (response);
}