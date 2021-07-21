#include "minishell.h"

int	check_flag(char **cmd_line, int *i)
{
	int	j;

	j = 2;
	if (ft_strncmp(cmd_line[*i], "-n", 2 != 0) || ft_strlen(cmd_line[*i]) < 2)
		return (0);
	while (cmd_line[(*i)])
	{
		if (ft_strncmp(cmd_line[*i], "-n", 2 != 0))
			return (1);
		else
		{
			while (cmd_line[*i][j])
			{
				if (cmd_line[*i][j] != 'n')
					return (1);
				j++;
			}
		}
		(*i)++;
	}
	return (1);
}

int	echo(char **cmd_line)
{
	int	i;
	int	flag_n;
	int	strings_amount;

	strings_amount = strings_counter(cmd_line);
	if (strings_amount == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	i = 1;
	flag_n = check_flag(cmd_line, &i);
	while (i < strings_amount && cmd_line[i])
	{
		ft_putstr_fd(cmd_line[i], STDOUT_FILENO);
		i++;
		if (i != strings_amount)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag_n)
		write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 0;
	return (0);
}
