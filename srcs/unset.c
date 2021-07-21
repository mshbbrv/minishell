#include "minishell.h"

char	**del_str_from_arr(char **old_arr, int n, int num_of_envp)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = malloc(sizeof(char *) * num_of_envp);
	while (i < n)
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	n = i + 1;
	while (old_arr[n])
	{
		new_arr[i] = ft_strdup(old_arr[n]);
		i++;
		n++;
	}
	new_arr[i] = NULL;
	free_splited_arr(old_arr);
	return (new_arr);
}

int	unset(char **cmd_line, t_data *data)
{
	int	i;
	int	num_of_envp;

	if (strings_counter(cmd_line) == 1)
		return (0);
	i = find_env_var(cmd_line[1], data->envp);
	if (i == -1)
		return (0);
	num_of_envp = strings_counter(data->envp);
	data->envp = del_str_from_arr(data->envp, i, num_of_envp);
	return (0);
}
