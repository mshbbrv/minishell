#include "minishell.h"

char	*positional_parameter(char *str, int start, int end)
{
	char	*env_value;
	char	*new_str;
	char	*merge_str;

	if (str[end - 1] == '0')
	{
		env_value = ft_strdup("minishell");
		new_str = ft_substr(str, 0, start);
		merge_str = ft_strjoin(new_str, env_value);
		if (new_str)
			free(new_str);
		if (env_value)
			free(env_value);
		new_str = ft_strjoin(merge_str, str + end);
		if (merge_str)
			free(merge_str);
	}
	else
	{
		merge_str = ft_substr(str, 0, start);
		new_str = ft_strjoin(merge_str, str + end);
		if (merge_str)
			free(merge_str);
	}
	return (new_str);
}

char	*exit_status_env(char *str, int start, int end)
{
	char	*env_value;
	char	*new_str;
	char	*merge_str;

	env_value = ft_itoa(g_exit_status);
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

char	*make_env_key(char *str, int *i, int start)
{
	char	*env_key;

	while (str[*i] == '_' || ft_isalnum(str[*i]) || str[*i] == '?')
		(*i)++;
	env_key = ft_substr(str, start + 1, *i - start - 1);
	return (env_key);
}
