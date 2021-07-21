#include "minishell.h"

char	**join_str_to_arr(char **old_arr, char *str)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = malloc(sizeof(char *) * (strings_counter(old_arr) + 2));
	while (old_arr[i])
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	i = 0;
	while (old_arr[i])
	{
		free(old_arr[i]);
		i++;
	}
	free(old_arr[i]);
	free(old_arr);
	return (new_arr);
}
