#include "minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error_handler(strerror(errno), 1);
		return (1);
	}
	else
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	return (0);
}
