#include "../header/minishell.h"

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
      return (response);
}