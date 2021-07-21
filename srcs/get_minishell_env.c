#include "minishell.h"

char	*get_minishell_env(char *key, char **env_vars)
{
	char	*value;
	int		i;
	int		j;

	i = find_env_var(key, env_vars);
	j = 0;
	if (i == -1)
		return (NULL);
	while (env_vars[i][j])
	{
		if (env_vars[i][j] == '=')
			break ;
		j++;
	}
	value = ft_substr(env_vars[i], j + 1, (ft_strlen(env_vars[i]) - j));
	return (value);
}
