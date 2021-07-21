#include "minishell.h"

void	change_envp_oldpwd(char *key, char *value, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!value)
		tmp = ft_strjoin(key, "=");
	else
		tmp = str_3_join(key, "=", value);
	while (data->envp[i])
	{
		if (ft_strncmp(key, data->envp[i], ft_strlen(key)) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		i++;
	}
	data->envp = join_str_to_arr(data->envp, tmp);
	free(tmp);
}

void	change_envp_pwd(char *key, char *value, t_data *data)
{
	char	*tmp;

	tmp = str_3_join(key, "=", value);
	if (check_and_change_env_vars(tmp, data) == -1)
		add_env_var(data, tmp);
	free(tmp);
}
