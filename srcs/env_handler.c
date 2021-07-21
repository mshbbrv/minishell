#include "minishell.h"

int	env_key_finder(char **envp, char *env_key)
{
	int		i;
	int		k;
	char	*current_key;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], env_key, ft_strlen(envp[i])))
		{
			k = 0;
			while (envp[i][k] != '=' && envp[i][k])
				k++;
			current_key = ft_substr(envp[i], 0, k);
			if (equal_str(env_key, current_key))
			{
				free(current_key);
				return (i);
			}
			free(current_key);
		}
		i++;
	}
	return (-1);
}

char	*key_not_found(char *str, int start, int end)
{
	char	*before_variable;
	char	*new_str;

	before_variable = ft_substr(str, 0, start);
	new_str = ft_strjoin(before_variable, str + end);
	if (before_variable)
		free(before_variable);
	return (new_str);
}

char	*key_found(char *env_str, char *str, int start, int end)
{
	char	*env_value;
	char	*new_str;
	char	*merge_str;
	int		i;

	i = 0;
	while (env_str[i] != '=' && env_str[i])
		i++;
	env_value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i);
	new_str = ft_substr(str, 0, start);
	merge_str = ft_strjoin(new_str, env_value);
	if (new_str)
		free(new_str);
	if (env_value)
		free(env_value);
	new_str = ft_strjoin(merge_str, str + end);
	if (merge_str)
		free(merge_str);
	return (new_str);
}

char	*find_correct_env(char *str, char **envp, int *i, int start)
{
	char	*env_key;
	int		line_number;
	char	*new_str;

	env_key = make_env_key(str, i, start);
	if (equal_str("?", env_key))
		new_str = exit_status_env(str, start, *i);
	else
	{
		line_number = env_key_finder(envp, env_key);
		if (line_number == -1)
			new_str = key_not_found(str, start, *i);
		else
			new_str = key_found(envp[line_number], str, start, *i);
	}
	free(env_key);
	return (new_str);
}

char	*env_handler(char *str, int *i, char **envp)
{
	char	*new_str;
	int		start;

	start = *i;
	(*i)++;
	if (ft_isdigit(str[*i]))
		new_str = positional_parameter(str, start, ++(*i));
	else
		new_str = find_correct_env(str, envp, i, start);
	free(str);
	*i = start;
	return (new_str);
}
