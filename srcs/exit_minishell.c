#include "minishell.h"

int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	check_cmd_lines(char **cmd_line)
{
	if (is_numeric_arg(cmd_line[1]) == 0 && strings_counter(cmd_line) > 2)
	{
		error_handler("exit: too many arguments", 1);
		return (1);
	}
	return (0);
}

int	exit_minishell(char **cmd_line, t_data *data)
{
	unsigned char	exit_arg;
	char			*tmp;

	(void)data;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd_line && cmd_line[1])
	{
		if (check_cmd_lines(cmd_line) == 1)
			return (1);
		if (strings_counter(cmd_line) >= 2
			&& (ft_strlen(cmd_line[1]) >= 20
				|| is_numeric_arg(cmd_line[1]) == -1))
		{
			tmp = str_3_join("exit: ", cmd_line[1],
					 	": numeric argument required");
			error_handler(tmp, 255);
			free(tmp);
		}
		else if (strings_counter(cmd_line) == 2)
		{
			exit_arg = ft_atoi(cmd_line[1]);
			g_exit_status = exit_arg;
		}
	}
	exit(g_exit_status);
}
