#include "minishell.h"

char	**sort_envp(char **envp, int i, int j)
{
	char	**sorted;
	int		n;
	char	*tmp;

	n = strings_counter(envp);
	sorted = copy_envp(envp);
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(sorted[i], sorted[j], ft_strlen(sorted[i])) > 0)
			{
				tmp = ft_strdup(sorted[i]);
				free(sorted[i]);
				sorted[i] = ft_strdup(sorted[j]);
				free(sorted[j]);
				sorted[j] = ft_strdup(tmp);
				free(tmp);
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

void	print_export(char **envp)
{
	int		i;
	int		j;
	int		flag;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		flag = 0;
		write(STDOUT_FILENO, "declare -x ", 11);
		while (envp[i][++j])
		{
			if (!flag && envp[i][j] == '=')
			{
				write(STDOUT_FILENO, "=\"", 2);
				flag = 1;
			}
			else
				write(STDOUT_FILENO, &envp[i][j], 1);
		}
		if (ft_strchr(envp[i], '='))
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
	}
	free_splited_arr(envp);
}

int	export(char **cmd_line, t_data *data)
{
	int		i;
	char	*tmp;

	i = 1;
	if (strings_counter(cmd_line) == 1)
	{
		print_export(sort_envp(data->envp, 0, 0));
		return (0);
	}
	while (cmd_line[i])
	{
		if (cmd_line[i][0] == '=')
		{
			tmp = str_3_join("export: `", cmd_line[1],
					 "': not a valid identifier");
			error_handler(tmp, 1);
			free(tmp);
			return (1);
		}
		if (check_and_change_env_vars(cmd_line[i], data) == -1)
			add_env_var(data, cmd_line[i]);
		i++;
	}
	return (0);
}
