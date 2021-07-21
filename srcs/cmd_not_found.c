#include "minishell.h"

void	cmd_not_found(char *cmd_line, t_data *data)
{
	reset_fd_to_default(data);
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(cmd_line, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putendl_fd("command not found", STDOUT_FILENO);
	g_exit_status = 127;
}
